#include "crawl_worker_factory.hpp"

CrawlWorkerFactory::CrawlWorkerFactory(){}

CrawlWorkerFactory::~CrawlWorkerFactory(){}

shared_ptr<CrawlWorker> CrawlWorkerFactory::get_crawl_worker(string name, Properties* properties)
{
    shared_ptr<CrawlWorker> crawl_worker = NULL;
    if(name == "AudioReaderCrawlWorker")
    {
        crawl_worker = make_shared<AudioReaderCrawlWorker>(properties);
    }
    else
    {
        crawl_worker = make_shared<MusicFileMetadataExtractorCrawlWorker>(properties);
    }

    return crawl_worker;
}