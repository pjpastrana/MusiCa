#include "fft_processor.hpp"

FFTProcessor::FFTProcessor()
{
    input_signal_ = NULL;
    output_transform_ = NULL;
    window_size_ = 256;
    signal_num_channels_ = 0;
}

FFTProcessor::~FFTProcessor()
{
    fftw_free(input_signal_);
    fftw_free(output_transform_);
    fftw_destroy_plan(plan_);
}

double* FFTProcessor::get_audio_data_buffer()
{
    return input_signal_;
}

void FFTProcessor::set_args(int window_size, int channels)
{
    window_size_ = window_size;
    signal_num_channels_ = channels;
}

void FFTProcessor::alloc_buffers_and_init_plan()
{
    // TODO: I think i need to use the number of channels to allocation
    if(!input_signal_)
        input_signal_ = (double*) fftw_malloc(sizeof(double) * window_size_);
    if(!output_transform_)
        output_transform_ = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * window_size_);

    if(!input_signal_ || !output_transform_)
    {
        std::cerr << "ERROR@fft_processor: Unable to allocate memory for sample buffers " << std::endl;
        return;
    }

    plan_ = fftw_plan_dft_r2c_1d(window_size_, input_signal_, output_transform_, FFTW_ESTIMATE);
    if(!plan_)
    {
        std::cerr << "ERROR@fft_processor: Fail to initialize plan  " << std::endl;
        return;
    }
}

fftw_complex* FFTProcessor::transform()
{
    fftw_execute(plan_);
    return output_transform_;
}