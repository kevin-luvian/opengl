#pragma once

#include <time.h>
#include <string>
#include <stdint.h>
#include "XorshiftP.h"
#include "Splitmix64.h"

// static const uint64_t BIG_PRIME = 0x7E94F28744587C87;

class RGEN
{
private:
    xorshift128p_state superState;
    xorshift128p_state state;

    void updateSuperState(uint64_t superSeed)
    {
        superState = {superSeed, Splitmix64::Random(superSeed)};
        state = superState;
    }

    void updateState(uint64_t seed) { state = createState(superState, seed); }
    void resetState() { state = superState; }

    uint64_t getRandom() { return XorshiftP::GetRandom(state); }
    uint64_t getQuickRandom(uint64_t seed)
    {
        auto sSeed = createState(superState, seed);
        return XorshiftP::QuickRandom(sSeed.a, sSeed.b);
    }

    RGEN()
    {
        uint64_t t = (unsigned)time(NULL);
        uint64_t tMix = Splitmix64::Random(t);
        superState = {tMix, tMix & t};
        state = superState;
    }
    static RGEN &GET()
    {
        static RGEN instance;
        return instance;
    }
    static xorshift128p_state createState(xorshift128p_state src, uint64_t num)
    {
        return {src.a & num, src.b & num};
    }

public:
    static void SuperSeed(std::string seedState) { GET().updateSuperState(std::hash<std::string>{}(seedState)); }
    static void SuperSeed(uint64_t seed) { GET().updateSuperState(Splitmix64::Random(seed)); }
    static void Seed(std::string seed) { GET().updateState(std::hash<std::string>{}(seed)); }
    static void Seed(uint64_t seed) { GET().updateState(Splitmix64::Random(seed)); }
    static void Reseed() { GET().resetState(); }

    static uint64_t NoUpdateRandom(std::string seed) { return GET().getQuickRandom(std::hash<std::string>{}(seed)); }
    static uint64_t NoUpdateRandom(uint64_t seed) { return GET().getQuickRandom(Splitmix64::Random(seed)); }
    static uint64_t NoUpdateRandom(uint64_t seed, uint32_t min, uint32_t max)
    {
        return NoUpdateRandom(seed) % (max - min) + min;
    }

    // main method to get random
    static uint64_t Random() { return GET().getRandom(); }

    static uint64_t Uint() { return Random(); }
    static uint64_t Uint(uint64_t min, uint64_t max)
    {
        return Uint() % (max - min) + min;
    }

    static int64_t Int64() { return Random(); }
    static int64_t Int64(int64_t min, int64_t max)
    {
        return Int64() % (max - min) + min;
    }

    static double_t Double() { return (double_t)Random() / (double_t)UINTMAX_MAX; }
    static double_t Double(double_t min, double_t max) { return Double() * (max - min) + min; }

    static glm::vec4 RandomColor()
    {
        return glm::vec4(Double(0.0, 255.0) / 255.0,
                         Double(0.0, 255.0) / 255.0,
                         Double(0.0, 255.0) / 255.0,
                         0.1);
    }
    static glm::vec3 RandomPosition(double range)
    {
        return glm::vec3(
            Double(-range, range),
            Double(-range, range),
            Double(-range, range));
    }

    static glm::mat4 RandomModel(double minScale, double maxScale)
    {
        glm::vec3 vRotation = glm::vec3(Double(), Double(), Double());
        glm::mat4 res(1.0);
        res = glm::rotate(res, util::toRadians(Double(0.0, 360.0)), vRotation);
        // res = glm::translate(res, pos);
        res = glm::scale(res, glm::vec3(Double(minScale, maxScale)));
        return res;
    }
};