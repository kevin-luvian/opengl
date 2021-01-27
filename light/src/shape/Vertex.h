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
        x *= invMag;
        y *= invMag;
        z *= invMag;
    }
    glm::vec3 toGlmVec3() const { return glm::vec3(x, y, z); }
    glm::vec4 toGlmVec4() const { return glm::vec4(x, y, z, 1.0); }
    Vertex cross(Vertex &other) const
    {
        return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
    }
    // add two Vertex values and return new Vertex
    Vertex operator+(const Vertex &other) const { return {x + other.x, y + other.y, z + other.z}; }
    // subtract two Vertex values and return new Vertex
    Vertex operator-(const Vertex &other) const { return {x - other.x, y - other.y, z - other.z}; }
    friend std::ostream &operator<<(std::ostream &out, const Vertex &v)
    {
        out << "x:" << v.x << ", y:" << v.y << ", z:" << v.z;
        return out;
    }
    static Vertex Convert(const glm::vec3 &vec) { return {vec.x, vec.y, vec.z}; }
};

struct VertexAttribute
{
    glm::vec3 normal;
    friend std::ostream &operator<<(std::ostream &out, const VertexAttribute &va)
    {
        out << "VertexAttribute["
            << " Normal(x:" << va.normal.x << ", y:" << va.normal.y << ", z:" << va.normal.z << ")"
            << " ]";
        return out;
    }
};