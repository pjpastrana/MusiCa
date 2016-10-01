#ifndef _FFT_PROCESSOR_H_
#define _FFT_PROCESSOR_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <fftw3.h>

using namespace std;

class FFTProcessor
{
    public:
        FFTProcessor();
        ~FFTProcessor();
        void transform(vector<double> signal);
};

#endif