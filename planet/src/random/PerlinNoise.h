#pragma once

#include "RGEN.h"

class PerlinNoise
{
public:
    PerlinNoise()
    {
        seed1DNoise(0);
        seed2DNoise(0, seeds2DWidth, seeds2DHeight);
    }
    PerlinNoise(uint64_t seed) {}
    void seed1DNoise(uint64_t seed);
    void seed2DNoise(uint64_t seed, uint64_t width, uint64_t height);
    double noise1D(unsigned int val);
    static double noise1D(DetailedArray<double> &seeds, unsigned int val);
    double noise2D(unsigned int x, unsigned int y);

    static double interpolate(DetailedArray<double> &seeds, unsigned int pitch, unsigned int index);

private:
    DetailedArray<double> seeds1D;
    DetailedArray<double> seeds2D;
    unsigned int seeds1DSize = 360;
    uint64_t seeds2DWidth = 360;
    uint64_t seeds2DHeight = 360;
};