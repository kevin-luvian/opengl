#pragma once

#include <time.h>
#include <stdint.h>

struct xorshift128p_state
{
    uint64_t a, b;
};

class XorshiftP
{
private:
    xorshift128p_state state;

public:
    XorshiftP() : XorshiftP({(unsigned)time(NULL), (unsigned)time(NULL)}) {}
    XorshiftP(xorshift128p_state _state) { seed(_state); }
    void seed(xorshift128p_state _state) { state = _state; }

    uint64_t getRandom()
    {
        uint64_t t = state.a;
        uint64_t const s = state.b;
        state.a = s;
        t ^= t << 23;       // a
        t ^= t >> 17;       // b
        t ^= s ^ (s >> 26); // c
        state.b = t;
        return t + s;
    }
};