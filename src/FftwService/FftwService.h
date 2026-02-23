#include <fftw3.h>
#include <cstdint>
#include <cstddef>

class FftwService
{
public:
	FftwService(int newFftSize);
	void fillFftwBuffer(const std::int16_t* samples, std::size_t currentSample);

	std::int16_t* samples;
	std::size_t sampleCount;

	double* in;
	fftw_complex* out;
	fftw_plan plan;
private:
	int fftSize;

};