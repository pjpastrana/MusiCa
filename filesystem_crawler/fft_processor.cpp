#include "fft_processor.hpp"

FFTProcessor::FFTProcessor()
{
    sample_input_signal_ = NULL;
    sample_output_transform_ = NULL;
    window_size_ = 256;
    signal_num_channels_ = 0;
}

FFTProcessor::~FFTProcessor()
{
    fftw_free(sample_input_signal_);
    fftw_free(sample_output_transform_);
    fftw_destroy_plan(sample_plan_);
}

double* FFTProcessor::get_audio_data_buffer()
{
    return sample_input_signal_;
}

void FFTProcessor::set_args(int window_size, int channels)
{
    window_size_ = window_size;
    signal_num_channels_ = channels;
}

void FFTProcessor::alloc_buffers_and_init_plan()
{
    if(!sample_input_signal_)
        sample_input_signal_ = (double*) fftw_malloc(sizeof(double) * window_size_);
    if(!sample_output_transform_)
        sample_output_transform_ = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * window_size_);

    if(!sample_input_signal_ || !sample_output_transform_)
    {
        std::cerr << "ERROR@fft_processor: Unable to allocate memory for sample buffers " << std::endl;
        return;
    }

    sample_plan_ = fftw_plan_dft_r2c_1d(window_size_, sample_input_signal_, sample_output_transform_, FFTW_ESTIMATE);
    if(!sample_plan_)
    {
        std::cerr << "ERROR@fft_processor: Fail to initialize plan  " << std::endl;
        return;
    }
}

fftw_complex* FFTProcessor::transform()
{
    fftw_execute(sample_plan_);
    return sample_output_transform_;
}