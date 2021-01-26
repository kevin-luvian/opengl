#pragma once

struct Vertex
{
    float x, y, z;
    static unsigned long count()
    {
        return 3;
    }
    void normalize()
    {
        // double invMag = 1 / sqrt(x * x + y * y + z * z);
        double invMag = util::fisqrt(x * x + y * y + z * z);
        scale(invMag);
    }
    void scale(float mag)
    {
        x *= mag;
        y *= mag;
        z *= mag;
    }
    void scaleNormal(float mag)
    {
        double invMag = util::fisqrt(x * x + y * y + z * z);
        scale(mag * invMag);
    }
    // add two Vertex attribute and return new Vertex
    Vertex operator+(Vertex &other) const { return {x + other.x, y + other.y, z + other.z}; }
    friend std::ostream &operator<<(std::ostream &out, const Vertex &v)
    {
        out << "x:" << v.x << ", y:" << v.y << ", z:" << v.z;
        return out;
    }
};