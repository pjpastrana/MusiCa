#ifndef _AUDIO_READER_CRAWL_WORKER_H_
#define _AUDIO_READER_CRAWL_WORKER_H_

#include <sndfile.h>
#include <vector>

#include "crawl_worker.hpp"
#include "file_metadata.hpp"
#include "properties.hpp"
#include "fft_processor.hpp"

// TODO: would become a generic class for reading different audio files
class AudioReaderCrawlWorker : public CrawlWorker
{
    shared_ptr<FileMetadata> audio_file_metadata_;
    vector<double> audio_data_;
    int audio_buffer_size_;
    FFTProcessor fft_processor;

    public:
        AudioReaderCrawlWorker(Properties* properties);
        ~AudioReaderCrawlWorker();
        shared_ptr<FileMetadata> do_something (const path file);
        bool is_valid_file(const path file);
        void read_audio_file(const path file);
        void process_audio_file();

};

#endif