#pragma once

struct Indice
{
    unsigned int top, left, right;
    static unsigned long count()
    {
        return 3;
    }
    unsigned int operator[](int i) const
    {
        switch (i)
        {
        case 0:
            return left;
        case 1:
            return top;
        case 2:
            return right;
        default:
            throw std::runtime_error("Indice index out of range");
        }
    }
    unsigned int &operator[](int i)
    {
        switch (i)
        {
        case 0:
            return left;
        case 1:
            return top;
        case 2:
            return right;
        default:
            throw std::runtime_error("Indice index out of range");
        }
    }
    friend std::ostream &operator<<(std::ostream &out, const Indice &t)
    {
        out << "top:" << t.top << ", left:" << t.left << ", right:" << t.right;
        return out;
    }
};