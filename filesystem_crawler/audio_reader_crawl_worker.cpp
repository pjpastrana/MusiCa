#include "audio_reader_crawl_worker.hpp"

AudioReaderCrawlWorker::AudioReaderCrawlWorker()
{}

AudioReaderCrawlWorker::~AudioReaderCrawlWorker()
{
    if(audio_data_ != NULL)
        delete audio_data_;
}

FileMetadata* AudioReaderCrawlWorker::do_something(const path file)
{
    cout << "AudioReaderCrawlWorker doing something with " << file.string() << endl;
    read_audio_file(file);
    process_audio_file();
    return NULL;
}

bool AudioReaderCrawlWorker::is_valid_file(const path file)
{
    return true;
}

const int AUDIO_BUFFER_SIZE = 1024;
#define ARRAY_LEN(x)    ((int) (sizeof (x) / sizeof (x [0])))

void AudioReaderCrawlWorker::read_audio_file(const path file)
{
    SNDFILE* infile = NULL;
    SF_INFO sfinfo;
    double audio_data_buffer[AUDIO_BUFFER_SIZE];
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

    // TODO: copy buffer content into propery
    do
    {
        num_samples_read = sf_read_double (infile, audio_data_buffer, ARRAY_LEN (audio_data_buffer) );
        num_total_samples_read += num_samples_read;
    } while ( num_samples_read > 0);
    sf_close(infile);
    cout << "num_total_samples_read " << num_total_samples_read << endl;
}

void AudioReaderCrawlWorker::process_audio_file()
{

}