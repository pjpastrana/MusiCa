#include "fft_processor.hpp"

FFTProcessor::FFTProcessor()
{}

FFTProcessor::~FFTProcessor()
{}

void FFTProcessor::transform(vector<double> signal)
{
    cout << "im going to transform the signal " << endl;
    fftw_complex *out;
    fftw_plan plan;
    int N = signal.size();
    double* signal_ptr = &signal[0];

    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    plan = fftw_plan_dft_r2c_1d(N, signal_ptr, out, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);

    // for(int i = 0; i < N/2; ++i)
    // {
    //     printf( "%i %f\n", i*21, sqrt(out[i][0]*out[i][0] + out[i][1]*out[i][1]) );
    // }

    fftw_free(out);
}