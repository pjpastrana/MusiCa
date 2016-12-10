#include "audio_reader_crawl_worker.hpp"

AudioReaderCrawlWorker::AudioReaderCrawlWorker(Properties* properties)
{
    audio_buffer_size_ = properties->get_int("audio_buffer_size");
}

AudioReaderCrawlWorker::~AudioReaderCrawlWorker()
{}

void AudioReaderCrawlWorker::do_something(const path file)
{
    if(exists(file) && is_regular_file(file) && is_valid_file(file))
    {
        // only working with user/data files (i.e. not hidden or system files)
        cout << "INFO@AudioReaderCrawlWorker.do_something: " << file.string() << endl;
        audio_filename_ = file.filename().string();
        read_audio_file(file);
        persist_metadata();
    }
}

bool AudioReaderCrawlWorker::is_valid_file(const path file)
{
    bool is_valid = false;
    // TODO: refactor. create some sort of class or enum with the vaid types
    if(file.extension() == ".wav")
        is_valid = true;
    return is_valid;
}

void AudioReaderCrawlWorker::read_audio_file(const path file)
{
    SNDFILE* infile = NULL;
    SF_INFO sfinfo = {0,0,0,0,0,0};
    sf_count_t num_samples_read = 0;
    sf_count_t num_total_samples_read = 0;

    cout << "INFO@AudioReaderCrawlWorker.read_audio_file: reading audio file " << endl;

    infile = sf_open(file.c_str(), SFM_READ, &sfinfo);
    if(!infile)
    {
        cerr << "ERROR@AudioReaderCrawlWorker.read_audio_file: Unable to open input file " << file.string() << endl;
        // TODO: how to handle errors
        return;
    }
    fft_processor_.set_args(audio_buffer_size_, sfinfo.channels);//, (double)sfinfo.samplerate);
    fft_processor_.alloc_buffers_and_init_plan();
    double* audio_data_buffer = fft_processor_.get_audio_data_buffer();
    do
    {
        num_samples_read = sf_read_double(infile, audio_data_buffer, audio_buffer_size_);
        num_total_samples_read += num_samples_read;
        zero_padding(num_samples_read, audio_data_buffer);
        process_audio(num_samples_read, num_total_samples_read, (double)sfinfo.samplerate);
        
        // TODO: what is this about channels?
        // account_signal_channels();
    } while ( num_samples_read > 0);
    sf_close(infile);

    cout << "num_total_samples_read " << num_total_samples_read << endl;
}

void AudioReaderCrawlWorker::zero_padding(int num_samples_read, double* audio_data_buffer)
{
    if(0 < num_samples_read && num_samples_read < audio_buffer_size_)
    {
        for(int n = num_samples_read; n < audio_buffer_size_; ++n)
        {
            audio_data_buffer[n] = 0.0;
        }
    }
}

#define REAL 0
#define IMAG 1

// Modulus of a Complex Number
static double imabs( const fftw_complex cpx )
{
    return sqrt( ( cpx[REAL] * cpx[REAL] ) + ( cpx[IMAG] * cpx[IMAG] ) );
}

void AudioReaderCrawlWorker::process_audio(int num_samples_read, int total_samples, double sample_rate)
{
    if(num_samples_read > 0)
    {
        fftw_complex* fft_transform = fft_processor_.transform();
        int samples = (audio_buffer_size_ / 2) + 1;
        double time_in_seconds = (double) total_samples / sample_rate;

        for(int i = 0; i < samples; ++i)
        {
            double frequency = (double)i * sample_rate / (double) samples;
            double magnitude = imabs(fft_transform[i]) / 2.0;
            
            vector<double> triplet;
            triplet.push_back(frequency);
            triplet.push_back(time_in_seconds);
            triplet.push_back(magnitude);
            audio_file_spectrogram_values_.push_back(triplet);
        }
    }
}

void AudioReaderCrawlWorker::persist_metadata()
{
    cout << "INFO@AudioReaderCrawlWorker.persist_metadata: Persisting spectrogram values" << endl;
    
    ofstream out;
    out.open(audio_filename_+".tsv");
    double time_change_mark = audio_file_spectrogram_values_[0][1];
    out << "# frequency\ttime_in_seconds\tmagnitude" << endl;
    
    for(auto spectrogram_value_triplet : audio_file_spectrogram_values_)
    {
        if(spectrogram_value_triplet[1] > time_change_mark)
        {
            out << endl;
            time_change_mark = spectrogram_value_triplet[1];
        }

        out << spectrogram_value_triplet[0] << "\t" 
            << spectrogram_value_triplet[1] << "\t" 
            << spectrogram_value_triplet[2] << endl;
    }
    out.close();
}

