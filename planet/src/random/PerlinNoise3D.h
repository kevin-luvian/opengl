#pragma once

#include "unit/vec2d.h"
#include "unit/vec3d.h"
#include "RGEN.h"

class PerlinNoise3D
{

public:
    PerlinNoise3D(
        float frequency = 1.00f,
        float lacunarity = 2.0f,
        float amplitude = 2.0f,
        float persistence = 0.5f);
    double noise(double x, double y) const;
    double noise(double x, double y, double z) const;
    double fractal(size_t octaves, double x, double y) const;
    double fractal(size_t octaves, double x, double y, double z) const;

private:
    DetailedArray<int> P;
    float mFrequency, mLacunarity, mAmplitude, mPersistence;

    void createPTable();
    void shuffle(DetailedArray<int> &table, unsigned int boundary);
    double interpolate(double t, double a1, double a2) const;
    double fade(double t) const;
};