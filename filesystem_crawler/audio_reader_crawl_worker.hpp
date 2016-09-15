#ifndef _AUDIO_READER_CRAWL_WORKER_H_
#define _AUDIO_READER_CRAWL_WORKER_H_

#include <sndfile.h>

#include "crawl_worker.hpp"

// TODO: would become a generic class for reading different audio files

class AudioReaderCrawlWorker : public CrawlWorker
{
    public:
        AudioReaderCrawlWorker();
        ~AudioReaderCrawlWorker();
        FileMetadata* do_something (const path file);
        bool is_valid_file(const path file);

};

#endif