#include "PerlinNoise.h"

// Static variables
static const unsigned int octaves = 5;

double PerlinNoise::interpolate(DetailedArray<double> &seeds, unsigned int pitch, unsigned int index)
{
    unsigned int val1 = index / pitch * pitch;
    unsigned int val2 = (val1 + pitch) % seeds.size;
    double blend = (double)(index - val1) / (double)pitch;
    double sample = (1.0 - blend) * seeds[val1] + (blend * seeds[val2]);
    return sample;
}
double PerlinNoise::noise1D(unsigned int val)
{
    return noise1D(seeds1D, val);
}
double PerlinNoise::noise1D(DetailedArray<double> &seeds, unsigned int val)
{
    unsigned int seedSize = seeds.size;
    double multiplier = 1.0;
    double scalingBias = 0.4;
    double res = 0.0;

    double scale = 1.0;
    double totalScale;
    unsigned int pitch;
    for (int i = 0; i < octaves; i++)
    {
        totalScale += scale;
        pitch = seedSize >> i;
        double sample = interpolate(seeds, pitch, val);
        res += scale * sample;
        scale /= scalingBias;
    }
    res /= totalScale;
    return res;
}
double PerlinNoise::noise2D(unsigned int x, unsigned int y)
{
    unsigned int seedW = seeds2DWidth;
    unsigned int seedH = seeds2DHeight;
    x = floor(x);
    y = floor(y);
    double multiplier = 1.0;
    double scalingBias = 1.7;
    double res = 0.0;

    double scale = 1.0;
    double totalScale, sample1, sample2, blend1, blend2;
    unsigned int pitch, pitchW, pitchH, valx1, valx2, valy1, valy2;
    for (int i = 0; i < octaves; i++)
    {
        // pitchW = seedW >> i;
        // pitchH = seedH >> i;
        pitch = seedW >> i;

        valx1 = x / pitch * pitch;
        valy1 = y / pitch * pitch;

        valx2 = (valx1 + pitch) % seedW;
        valy2 = (valy1 + pitch) % seedH;

        blend1 = (double)(x - valx1) / (double)pitch;
        blend2 = (double)(y - valy1) / (double)pitch;

        sample1 = (1.0 - blend1) * seeds2D[valy1 * seedW + valx1] + (blend1 * seeds2D[valy1 * seedW + valx2]);
        sample2 = (1.0 - blend1) * seeds2D[valy2 * seedW + valx1] + (blend1 * seeds2D[valy2 * seedW + valx2]);

        res += (blend2 * (sample2 - sample1) + sample1) * scale;
        scale /= scalingBias;
        totalScale += scale;
    }
    res /= totalScale;
    return res;
}
void PerlinNoise::seed1DNoise(uint64_t seed)
{
    if (seed > 0)
        RGEN::Seed(seed);
    seeds1D.data = RGEN::DoubleArray(seeds1DSize);
    seeds1D.size = seeds1DSize;
}
void PerlinNoise::seed2DNoise(uint64_t seed, uint64_t width, uint64_t height)
{
    if (seed > 0)
        RGEN::Seed(seed);
    seeds2DWidth = width;
    seeds2DHeight = height;
    auto size = seeds2DWidth * seeds2DHeight;
    seeds2D.data = RGEN::DoubleArray(size);
    seeds2D.size = size;
}