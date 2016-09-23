#include "audio_reader_crawl_worker.hpp"

#define ARRAY_LEN(x) ((int) (sizeof (x) / sizeof (x [0])))

AudioReaderCrawlWorker::AudioReaderCrawlWorker(Properties* properties)
{
    audio_file_metadata_ = NULL;
    audio_buffer_size_ = properties->get_int("audio_buffer_size");
}

AudioReaderCrawlWorker::~AudioReaderCrawlWorker()
{}

shared_ptr<FileMetadata> AudioReaderCrawlWorker::do_something(const path file)
{
    shared_ptr<FileMetadata> file_metadata = NULL;
    if(exists(file) && is_regular_file(file) && is_valid_file(file))
    {
        // only working with user/data files (i.e. not hidden or system files)
        cout << "AudioReaderCrawlWorker doing something with " << file.string() << endl;
        read_audio_file(file);
        process_audio_file();
    }
    return file_metadata;
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
    double audio_data_buffer[audio_buffer_size_];
    sf_count_t num_samples_read = 0;
    sf_count_t num_total_samples_read = 0;

    cout << "reading audio file " << endl;

    infile = sf_open(file.c_str(), SFM_READ, &sfinfo);
    if(!infile)
    {
        cerr << "ERROR@audio_reader_crawl_worker.read_audio_file: Unable to open input file " << file.string() << endl;
        // TODO: how to handle errors
        exit(1);
    }
    do
    {
        num_samples_read = sf_read_double (infile, audio_data_buffer, ARRAY_LEN (audio_data_buffer) );
        // add buffered samples to container
        for(int i = 0; i < num_samples_read; ++i)
            audio_data_.push_back(audio_data_buffer[i]);
        num_total_samples_read += num_samples_read;
    } while ( num_samples_read > 0);
    sf_close(infile);

    cout << "num_total_samples_read " << num_total_samples_read << endl;
}

void AudioReaderCrawlWorker::process_audio_file()
{

}