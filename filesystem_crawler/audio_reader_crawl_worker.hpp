#ifndef _AUDIO_READER_CRAWL_WORKER_H_
#define _AUDIO_READER_CRAWL_WORKER_H_

#include <sndfile.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "crawl_worker.hpp"
#include "file_metadata.hpp"
#include "properties.hpp"
#include "fft_processor.hpp"

// TODO: would become a generic class for reading different audio files
class AudioReaderCrawlWorker : public CrawlWorker
{
    // TODO: I dont like having the filename as a member variable
    string audio_filename_;
    vector< vector<double> > audio_file_spectrogram_values_;
    int audio_buffer_size_;
    FFTProcessor fft_processor_;

    public:
        AudioReaderCrawlWorker(Properties* properties);
        ~AudioReaderCrawlWorker();
        void do_something (const path file);
        bool is_valid_file(const path file);
        void read_audio_file(const path file);
        void zero_padding(int num_samples_read, double* audio_data_buffer);
        void process_audio(int num_samples_read, int num_total_samples_read, double sample_rate);
        void persist_metadata();

};

#endif