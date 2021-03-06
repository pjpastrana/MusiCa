#ifndef _MUSIC_FILE_METADATA_EXTRACTOR_CRAWL_WORKER_H_
#define _MUSIC_FILE_METADATA_EXTRACTOR_CRAWL_WORKER_H_

#include <fileref.h>
#include <tag.h>
#include <tpropertymap.h>

#include "crawl_worker.hpp"
#include "music_file_metadata.hpp"
#include "properties.hpp"
#include "utils.hpp"

class MusicFileMetadataExtractorCrawlWorker : public CrawlWorker
{
    shared_ptr<MusicFileMetadata> music_file_metadata_;

    public:
        MusicFileMetadataExtractorCrawlWorker(Properties* properties);
        ~MusicFileMetadataExtractorCrawlWorker();
        void do_something (const path file);
        bool is_valid_file(const path file);
        void extract_tags_from_file(const path file);
        void persist_metadata();
};

#endif
