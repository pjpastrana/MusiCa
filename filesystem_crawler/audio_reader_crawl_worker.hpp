#ifndef _AUDIO_READER_CRAWL_WORKER_H_
#define _AUDIO_READER_CRAWL_WORKER_H_

#include <fftw3.h>
#include <sndfile.h>

#include "crawl_worker.hpp"
#include "file_metadata.hpp"

// TODO: would become a generic class for reading different audio files

class AudioReaderCrawlWorker : public CrawlWorker
{
    FileMetadata* audio_file_metadata_;
    double* audio_data_;

    public:
        AudioReaderCrawlWorker();
        ~AudioReaderCrawlWorker();
        FileMetadata* do_something (const path file);
        bool is_valid_file(const path file);
        void read_audio_file(const path file);
        void process_audio_file();

};

#endif