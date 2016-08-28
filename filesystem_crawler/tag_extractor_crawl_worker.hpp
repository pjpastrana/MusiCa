#ifndef _TAG_EXTRACTOR_CRAWL_WORKER_H_
#define _TAG_EXTRACTOR_CRAWL_WORKER_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <fileref.h>
#include <tag.h>
#include <tpropertymap.h>

#include "crawl_worker.hpp"

class TagExtractorCrawlWorker : public CrawlWorker{

    public:
        TagExtractorCrawlWorker();
        ~TagExtractorCrawlWorker();
        void do_something (const path file);
        void extract_tags_from_file(const path file);
};

#endif
