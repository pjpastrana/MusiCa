#ifndef _CRAWL_WORKER_FACTORY_H_
#define _CRAWL_WORKER_FACTORY_H_

#include <string>

#include "music_file_metadata_extractor_crawl_worker.hpp"
#include "audio_reader_crawl_worker.hpp"
#include "properties.hpp"

class CrawlWorkerFactory
{
    CrawlWorkerFactory();
    public:
        ~CrawlWorkerFactory();
        static shared_ptr<CrawlWorker> get_crawl_worker(std::string name, Properties* properties);

};

#endif