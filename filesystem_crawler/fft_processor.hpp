#ifndef _FFT_PROCESSOR_H_
#define _FFT_PROCESSOR_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <fftw3.h>

using namespace std;

class FFTProcessor
{
    int window_size_;
    int signal_num_channels_;
    double* input_signal_;
    fftw_complex* output_transform_;
    fftw_plan plan_;

    public:
        FFTProcessor();
        ~FFTProcessor();
        void set_args(int window_size, int channels);
        double* get_audio_data_buffer();
        void alloc_buffers_and_init_plan();
        fftw_complex* transform();
};

#endif