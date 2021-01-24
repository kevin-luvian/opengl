#pragma once

#include "unit/vec2d.h"
#include "RGEN.h"

class PerlinNoise2D
{

public:
    PerlinNoise2D() { generatePermutationTable(); }

    double noise(double x, double y) const;
    double fractal(size_t octaves, double x, double y) const;

private:
    DetailedArray<unsigned int> mPermutations;
    static unsigned int Perm[];

    const int pTableSize = 256;

    void generatePermutationTable();
    vec2d getGradientVector(unsigned int n) const;
    double interpolate(double t, double a1, double a2) const;
    double fade(double t) const;
};