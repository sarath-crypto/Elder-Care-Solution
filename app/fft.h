#ifndef FFT_H_
#define FFT_H_

#include <iostream>
#include <fstream>
#include <math.h>
#include <fftw3.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <math.h>
#include "fb.h"
#include "filters.h"
#include "kissfft/kiss_fftr.h"

#define PI 3.1415926
#define SAMPLE_RATE 8000
#define FFT_SZ	1024

using namespace std;

class fft{
private:
       	Filter *phpf;

	pa_simple *s;

	kiss_fftr_cfg cfg;
	kiss_fft_scalar in[FFT_SZ];
	kiss_fft_cpx out[FFT_SZ/2 + 1];

	double cth;
public:
        vector <double> sig;
	bool en;
	bool voice;

	fft(unsigned char,unsigned short);
	~fft();
	void process(bool);
};

#endif 
