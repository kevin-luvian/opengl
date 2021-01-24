#include "PerlinNoise2D.h"

unsigned int PerlinNoise2D::Perm[256] = {151, 160, 137, 91, 90, 15,
                                         131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23,
                                         190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
                                         88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
                                         77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
                                         102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196,
                                         135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123,
                                         5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42,
                                         223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
                                         129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
                                         251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
                                         49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
                                         138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180};

void shuffle(DetailedArray<unsigned int> &table, unsigned int boundary)
{
    unsigned int i2;
    for (unsigned int i = 0; i < boundary; i++)
    {
        i2 = RGEN::Uint(0, boundary);
        table.swap(i, i2);
    }
}

void PerlinNoise2D::generatePermutationTable()
{
    mPermutations.make_empty(pTableSize);
    for (unsigned int i = 0; i < pTableSize; i++)
    {
        mPermutations[i] = Perm[i];
    }

    // for (unsigned int i = 0; i < pTableSize; i++)
    // {
    //     mPermutations[i] = i;
    // }
    // shuffle
    // shuffle(mPermutations, pTableSize);
    // double array
    // for (unsigned int i = 0; i < pTableSize; i++)
    // {
    //     mPermutations[pTableSize + i] = mPermutations[i];
    // }
    // mPermutations.print();
}

vec2d PerlinNoise2D::getGradientVector(unsigned int n) const
{
    n = n & 3;
    if (n == 0)
        return {1.0, 1.0};
    else if (n == 1)
        return {-1.0, 1.0};
    else if (n == 2)
        return {-1.0, -1.0};
    else
        return {1.0, -1.0};
}

double PerlinNoise2D::noise(double x, double y) const
{
    int X = util::ffloor(x);
    int Y = util::ffloor(y);

    double xf = x - X;
    double yf = y - Y;

    X = X & 255;
    Y = Y & 255;

    vec2d tR = {xf - 1.0, yf - 1.0};
    vec2d tL = {xf, yf - 1.0};
    vec2d bR = {xf - 1.0, yf};
    vec2d bL = {xf, yf};

    // vec2d bL = {xf, yf};
    // vec2d bR = {xf - 1.0, yf};
    // vec2d tR = {xf - 1.0, yf - 1.0};
    // vec2d tL = {xf, yf - 1.0};

    unsigned int gTL = Perm[(Perm[X + 1] + Y + 1) & 255];
    unsigned int gTR = Perm[(Perm[X] + Y + 1) & 255];
    unsigned int gBR = Perm[(Perm[X + 1] + Y) & 255];
    unsigned int gBL = Perm[(Perm[X] + Y) & 255];

    vec2d vTL = getGradientVector(gTL);
    vec2d vTR = getGradientVector(gTR);
    vec2d vBR = getGradientVector(gBR);
    vec2d vBL = getGradientVector(gBL);

    double dTL = tL.dot(vTL);
    double dTR = tR.dot(vTR);
    double dBR = bR.dot(vBR);
    double dBL = bL.dot(vBL);

    double u = fade(xf);
    double v = fade(yf);

    double result = interpolate(u, interpolate(v, dBL, dTL), interpolate(v, dBR, dTR));

    return result;
}

double PerlinNoise2D::fractal(size_t octaves, double x, double y) const
{
    float output = 0.f;
    float denom = 0.f;
    float frequency = 0.4f;
    float amplitude = 1.0f;
    float lacunarity = 4.0f;
    float persistence = 1 / lacunarity;

    for (size_t i = 0; i < octaves; i++)
    {
        output += (amplitude * noise(x * frequency, y * frequency));
        denom += amplitude;

        frequency *= lacunarity;
        amplitude *= persistence;
    }

    return (output / denom);
}

double PerlinNoise2D::interpolate(double t, double a1, double a2) const
{
    // return (1 - t) * a1 + t * a2;
    return a1 + t * (a2 - a1);
}

double PerlinNoise2D::fade(double t) const
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}