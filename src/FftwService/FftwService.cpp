#include "FftwService.h"
#include <vector>

FftwService::FftwService(int newFftSize) : fftSize(newFftSize)
{
	in = (double*)fftw_malloc(sizeof(double) * fftSize);
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * (fftSize / 2 + 1));
	plan = fftw_plan_dft_r2c_1d(fftSize, in, out, FFTW_ESTIMATE);
}

void FftwService::fillFftwBuffer(const std::int16_t* samples, std::size_t currentSample)
{
    for (int i = 0; i < fftSize; i++) {
        in[i] = (samples[currentSample + i] / 32768.0) / 2;
    }
    fftw_execute(plan);
}
