#include <SFML/Graphics.hpp>
#include <fftw3.h>

#include <vector>
#include <cmath>
#include <iostream>
#include <cstdint>

#include "SphereVisualiser/SphereVisualiser.h"
#include "FftwService/FftwService.h"
#include "AudioService/AudioService.h"

const int FFT_SIZE = 1024;
const int BAR_COUNT = 360;
