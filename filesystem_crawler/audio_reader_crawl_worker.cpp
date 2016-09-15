#include "audio_reader_crawl_worker.hpp"

AudioReaderCrawlWorker::AudioReaderCrawlWorker()
{}

AudioReaderCrawlWorker::~AudioReaderCrawlWorker()
{}

FileMetadata* AudioReaderCrawlWorker::do_something(const path file)
{
    cout << "Doing something to item " << file.string() << endl;
    return NULL;
}

bool AudioReaderCrawlWorker::is_valid_file(const path file)
{
    return true;
}