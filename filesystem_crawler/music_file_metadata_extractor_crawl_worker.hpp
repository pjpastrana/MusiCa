#ifndef _MUSIC_FILE_METADATA_EXTRACTOR_CRAWL_WORKER_H_
#define _MUSIC_FILE_METADATA_EXTRACTOR_CRAWL_WORKER_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <fileref.h>
#include <tag.h>
#include <tpropertymap.h>

#include "crawl_worker.hpp"
#include "music_file_metadata.hpp"

class MusicFileMetadataExtractorCrawlWorker : public CrawlWorker{

    MusicFileMetadata* music_file_metadata_;

    public:
        MusicFileMetadataExtractorCrawlWorker();
        ~MusicFileMetadataExtractorCrawlWorker();
        FileMetadata* do_something (const path file);
        bool is_valid_file(const path file);
        void extract_tags_from_file(const path file);
};

#endif
