#ifndef _AUDIO_READER_CRAWL_WORKER_H_
#define _AUDIO_READER_CRAWL_WORKER_H_

#include <fftw3.h>
#include <sndfile.h>
#include <list>

#include "crawl_worker.hpp"
#include "file_metadata.hpp"
#include "properties.hpp"

// TODO: would become a generic class for reading different audio files
class AudioReaderCrawlWorker : public CrawlWorker
{
    shared_ptr<FileMetadata> audio_file_metadata_;
    list<double> audio_data_;
    int audio_buffer_size_;

    public:
        AudioReaderCrawlWorker(Properties* properties);
        ~AudioReaderCrawlWorker();
        shared_ptr<FileMetadata> do_something (const path file);
        bool is_valid_file(const path file);
        void read_audio_file(const path file);
        void process_audio_file();

};

#endif