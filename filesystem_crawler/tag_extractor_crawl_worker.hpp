#ifndef _TAG_EXTRACTOR_CRAWL_WORKER_H_
#define _TAG_EXTRACTOR_CRAWL_WORKER_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <fileref.h>
#include <tag.h>
#include <tpropertymap.h>

#include "crawl_worker.hpp"
#include "audio_file_metadata.hpp"

// TODO: change name to AudioTagExtractorCrawlWorker
class TagExtractorCrawlWorker : public CrawlWorker{

    AudioFileMetadata* audio_file_metadata_;

    public:
        TagExtractorCrawlWorker();
        ~TagExtractorCrawlWorker();
        FileMetadata* do_something (const path file);
        bool is_valid_file(const path file);
        void extract_tags_from_file(const path file);
};

#endif
