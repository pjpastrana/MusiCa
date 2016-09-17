#ifndef _CRAWL_WORKER_FACTORY_H_
#define _CRAWL_WORKER_FACTORY_H_

#include <string>

// #include "crawl_worker.hpp"
#include "music_file_metadata_extractor_crawl_worker.hpp"

class CrawlWorkerFactory
{
    CrawlWorkerFactory();
    public:
        ~CrawlWorkerFactory();
        static CrawlWorker* get_crawl_worker(std::string name);

};

#endif