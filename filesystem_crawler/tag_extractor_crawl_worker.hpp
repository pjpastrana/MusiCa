#ifndef _TAG_EXTRACTOR_CRAWL_WORKER_H_
#define _TAG_EXTRACTOR_CRAWL_WORKER_H_

#include <iostream>
#include <string>

#include "crawl_worker.hpp"

class TagExtractorCrawlWorker : public CrawlWorker{

    public:
        TagExtractorCrawlWorker();
        ~TagExtractorCrawlWorker();
        void do_something (const path file);
};

#endif
