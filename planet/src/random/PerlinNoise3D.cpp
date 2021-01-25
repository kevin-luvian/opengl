#include "PerlinNoise3D.h"

static const int PermSize = 256;
static const int Perm[256] = {
    218, 51, 129, 213, 245, 168, 109, 224, 31, 57, 209, 188, 148, 47, 153, 131,
    2, 36, 248, 194, 96, 193, 16, 62, 72, 130, 68, 94, 147, 39, 158, 4,
    100, 27, 201, 215, 223, 163, 252, 7, 102, 236, 133, 84, 63, 169, 46, 173,
    5, 230, 141, 13, 162, 181, 103, 83, 15, 55, 184, 155, 229, 235, 50, 65,
    199, 178, 246, 121, 145, 56, 88, 78, 185, 197, 77, 37, 242, 179, 196, 33,
    66, 79, 8, 45, 232, 108, 26, 43, 166, 24, 187, 116, 198, 206, 82, 125,
    93, 76, 12, 19, 176, 106, 189, 241, 97, 75, 0, 22, 254, 239, 249, 204,
    164, 123, 20, 120, 91, 219, 73, 144, 11, 220, 115, 202, 253, 228, 233, 250,
    80, 25, 23, 89, 86, 35, 195, 227, 180, 238, 112, 161, 212, 208, 183, 167,
    132, 159, 143, 30, 114, 38, 222, 101, 251, 90, 247, 217, 67, 10, 207, 214,
    118, 200, 28, 243, 119, 124, 3, 48, 14, 74, 221, 60, 234, 52, 61, 244,
    211, 203, 205, 21, 190, 138, 231, 192, 255, 165, 237, 107, 17, 92, 54, 122,
    117, 59, 1, 81, 42, 18, 156, 9, 157, 40, 127, 151, 137, 142, 110, 104,
    99, 154, 174, 140, 85, 87, 98, 175, 41, 71, 111, 226, 34, 49, 170, 146,
    172, 186, 136, 128, 150, 32, 29, 182, 126, 135, 139, 225, 134, 210, 149, 177,
    113, 191, 53, 95, 216, 6, 70, 64, 69, 152, 240, 44, 171, 105, 160, 58};

static const vec3d G3D[12] = {{1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0}, {1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1}, {0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}};
static const vec2d G2D[4] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

PerlinNoise3D::PerlinNoise3D(
    float frequency,
    float lacunarity,
    float amplitude,
    float persistence)
{
    mFrequency = frequency;
    mLacunarity = lacunarity;
    mAmplitude = amplitude;
    mPersistence = persistence;
    createPTable();
}

void PerlinNoise3D::createPTable()
{
    P.make_empty(PermSize * 3);
    for (int i = 0; i < PermSize; i++)
    {
        P[i] = Perm[i];
    }
    shuffle(P, PermSize);
    for (int i = 0; i < PermSize * 2; i++)
    {
        P[i + PermSize] = P[i & (PermSize - 1)];
    }
}

void PerlinNoise3D::shuffle(DetailedArray<int> &table, unsigned int boundary)
{
    unsigned int i2;
    for (unsigned int i = 0; i < boundary; i++)
    {
        i2 = RGEN::Uint(0, boundary);
        table.swap(i, i2);
    }
}

double PerlinNoise3D::noise(double x, double y) const
{
    int X = util::ffloor(x) & 255;
    int Y = util::ffloor(y) & 255;

    x -= util::ffloor(x);
    y -= util::ffloor(y);

    // Calculate a set of four hashed gradient indices
    unsigned int gi00 = P[P[X] + Y] % 4;
    unsigned int gi01 = P[P[X] + Y + 1] % 4;
    unsigned int gi10 = P[P[X + 1] + Y] % 4;
    unsigned int gi11 = P[P[X + 1] + Y + 1] % 4;

    // Get dot product for each corner
    double d00 = G2D[gi00].dot({x, y});
    double d01 = G2D[gi01].dot({x, y - 1.0});
    double d10 = G2D[gi10].dot({x - 1.0, y});
    double d11 = G2D[gi11].dot({x - 1.0, y - 1.0});

    x = fade(x);
    y = fade(y);

    return interpolate(y, interpolate(x, d00, d10), interpolate(x, d01, d11));
}

double PerlinNoise3D::fractal(size_t octaves, double x, double y) const
{
    double frequency = mFrequency;
    double amplitude = mAmplitude;
    double ampAcc = amplitude;
    double noises;
    for (int i = 0; i < octaves; i++)
    {
        noises += noise(x * frequency, y * frequency) * amplitude;
        frequency *= mLacunarity;
        amplitude /= mPersistence;
        ampAcc += amplitude;
    }
    return noises / ampAcc;
}

double PerlinNoise3D::noise(double x, double y, double z) const
{
    int X = util::ffloor(x);
    int Y = util::ffloor(y);
    int Z = util::ffloor(z);

    x -= X;
    y -= Y;
    z -= Z;

    X &= 255;
    Y &= 255;
    Z &= 255;

    // Calculate a set of eight hashed gradient indices
    int gi000 = P[X + P[Y + P[Z]]] % 12;
    int gi001 = P[X + P[Y + P[Z + 1]]] % 12;
    int gi010 = P[X + P[Y + 1 + P[Z]]] % 12;
    int gi011 = P[X + P[Y + 1 + P[Z + 1]]] % 12;

    int gi100 = P[X + 1 + P[Y + P[Z]]] % 12;
    int gi101 = P[X + 1 + P[Y + P[Z + 1]]] % 12;
    int gi110 = P[X + 1 + P[Y + 1 + P[Z]]] % 12;
    int gi111 = P[X + 1 + P[Y + 1 + P[Z + 1]]] % 12;

    // vectors inside cube
    vec3d v000 = {x, y, z};
    vec3d v001 = {x, y, z - 1.0};
    vec3d v010 = {x, y - 1.0, z};
    vec3d v011 = {x, y - 1.0, z - 1.0};

    vec3d v100 = {x - 1.0, y, z};
    vec3d v101 = {x - 1.0, y, z - 1.0};
    vec3d v110 = {x - 1.0, y - 1.0, z};
    vec3d v111 = {x - 1.0, y - 1.0, z - 1.0};

    // dot products
    double d000 = v000.dot(G3D[gi000]);
    double d001 = v001.dot(G3D[gi001]);
    double d010 = v010.dot(G3D[gi010]);
    double d011 = v011.dot(G3D[gi011]);

    double d100 = v100.dot(G3D[gi100]);
    double d101 = v101.dot(G3D[gi101]);
    double d110 = v110.dot(G3D[gi110]);
    double d111 = v111.dot(G3D[gi111]);

    double u = fade(x);
    double v = fade(y);
    double w = fade(z);

    // interpolate x-axis
    double ix00 = interpolate(u, d000, d100);
    double ix01 = interpolate(u, d001, d101);
    double ix10 = interpolate(u, d010, d110);
    double ix11 = interpolate(u, d011, d111);

    // interpolate y-axis
    double iy0 = interpolate(v, ix00, ix10);
    double iy1 = interpolate(v, ix01, ix11);

    // interpolate z-axis
    double iz = interpolate(w, iy0, iy1);

    return iz;
}

double PerlinNoise3D::fractal(size_t octaves, double x, double y, double z) const
{
    double frequency = mFrequency;
    double amplitude = mAmplitude;
    double ampAcc = amplitude;
    double noises;
    for (int i = 0; i < octaves; i++)
    {
        noises += noise(x * frequency, y * frequency, z * frequency) * amplitude;
        frequency *= mLacunarity;
        amplitude /= mPersistence;
        ampAcc += amplitude;
    }
    return noises / ampAcc;
}

double PerlinNoise3D::interpolate(double t, double a1, double a2) const
{
    return a1 + t * (a2 - a1);
}

double PerlinNoise3D::fade(double t) const
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}