#pragma once

struct xorshift128p_state
{
    uint64_t a, b;
};

namespace XorshiftP
{
    static uint64_t GetRandom(xorshift128p_state &state)
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

    static uint64_t QuickRandom(uint64_t t, uint64_t const s)
    {
        t ^= t << 23;       // a
        t ^= t >> 17;       // b
        t ^= s ^ (s >> 26); // c
        return t + s;
    }
}