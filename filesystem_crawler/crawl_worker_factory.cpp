#include "crawl_worker_factory.hpp"

CrawlWorkerFactory::CrawlWorkerFactory(){}

CrawlWorkerFactory::~CrawlWorkerFactory(){}

CrawlWorker* CrawlWorkerFactory::get_crawl_worker(string name)
{
    CrawlWorker* crawl_worker = NULL;
    if(name == "AudioReaderCrawlWorker")
    {
        crawl_worker = new AudioReaderCrawlWorker();
    }
    else
    {
        crawl_worker = new MusicFileMetadataExtractorCrawlWorker();
    }

    return crawl_worker;
}