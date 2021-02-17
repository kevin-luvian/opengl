#pragma once

struct Indice
{
    unsigned int left, right, top;

    Indice() : left(0), right(0), top(0) {}
    Indice(unsigned int l, unsigned int r, unsigned int t) : left(l), right(r), top(t) {}
    Indice(const unsigned int *face) : left(face[0]), right(face[1]), top(face[2]) {}

    friend std::ostream &operator<<(std::ostream &out, const Indice &o)
    {
        out << "(t:" << o.top << ", l:" << o.left << ", r:" << o.right << ")";
        return out;
    }
};