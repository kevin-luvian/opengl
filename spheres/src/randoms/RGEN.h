#pragma once

#include <string>
#include <stdint.h>
#include "XorshiftP.h"

static const uint64_t BIG_PRIME = 9121181808113253511;
static const uint64_t BIG_PRIME_2 = 4973033695059416927;

class RGEN
{
private:
    XorshiftP generator;
    xorshift128p_state superState;

    void updateState(xorshift128p_state seed) { generator.seed({superState.a & seed.a, superState.b & seed.b}); }
    void updateSuperState(xorshift128p_state superSeed)
    {
        superState = superSeed;
        resetState();
    }

    void updateState(uint64_t seed) { updateState({superState.a & seed + BIG_PRIME, superState.b & seed + BIG_PRIME_2}); }
    void updateSuperState(uint64_t superSeed) { updateSuperState({superSeed & BIG_PRIME, superSeed & BIG_PRIME_2}); }

    void resetState() { generator.seed(superState); }
    uint64_t getRandom() { return generator.getRandom(); }

    RGEN() { superState = {(unsigned)time(NULL), (unsigned)time(NULL)}; }
    static RGEN &GET()
    {
        static RGEN instance;
        return instance;
    }

public:
    static void SuperSeed(std::string seedState) { GET().updateSuperState(std::hash<std::string>{}(seedState)); }
    static void Seed(std::string seed) { GET().updateState(std::hash<std::string>{}(seed)); }
    static void Seed(uint64_t seed) { GET().updateState(seed); }
    static void Reseed() { GET().resetState(); }

    // main method to get random
    static uint64_t Random() { return GET().getRandom(); }

    static uint64_t Uint() { return Random(); }
    static uint64_t Uint(uint64_t min, uint64_t max)
    {
        uint64_t rand = Uint();
        rand = Uint() % (max - min);
        return Uint() % (max - min) + min;
    }

    static int64_t Int64() { return Random(); }
    static int64_t Int64(int64_t min, int64_t max)
    {
        return Int64() % (max - min) + min;
    }

    static double_t Double() { return (double_t)Random() / (double_t)UINTMAX_MAX; }
    static double_t Double(double_t min, double_t max) { return Double() * (max - min) + min; }
};