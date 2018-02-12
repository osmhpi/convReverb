#pragma once

#include <cstdint>

// including this make fftw3 use std::complex instead of double[2] for complex
// values which is essential for storing them in a vector
#include <complex>
#include <fftw3.h>
#include <vector>

namespace gpuconv {

    uint32_t
    oAReverb(float *target, uint32_t targetFrames, float *impulsesx, float *impulsedx, uint32_t impulseFrames,
             float *outputsx, float *outputdx);

    uint32_t padTargetSignal(float *target, uint32_t segmentCount, uint32_t segmentSize,
                             std::vector<fftw_complex> &destinationBuffer);

    uint32_t convolve(fftw_complex *targetSignal,
                      fftw_complex *impulseSignal,
                      fftw_complex *intermediateSignal,
                      fftw_complex *transformedSignal,
                      uint32_t sampleSize);

    float mergeConvolvedSignal(std::vector<fftw_complex> &longInputBuffer, std::vector<fftw_complex> &shortOutpuBuffer,
                               uint32_t sampleSize, uint32_t sampleCount);

    void printComplexArray(fftw_complex *target, uint32_t size);

    inline float maximum(float maxo, float value);
}