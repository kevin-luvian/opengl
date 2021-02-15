#pragma once

struct Indice
{
    unsigned int left, right, top;

    friend std::ostream &operator<<(std::ostream &out, const Indice &o)
    {
        out << "(t:" << o.top << ", l:" << o.left << ", r:" << o.right << ")";
        return out;
    }
};