#pragma once

#include "unit/vec3d.h"
#include "RGEN.h"

class PerlinNoise3D
{

public:
    PerlinNoise3D();
    double noise(double x, double y, double z) const;
    double fractal(size_t octaves, double x, double y, double z) const;

private:
    DetailedArray<int> P;

    void shuffle(DetailedArray<int> &table, unsigned int boundary);
    void generatePermutationTable();
    double interpolate(double t, double a1, double a2) const;
    double fade(double t) const;
};