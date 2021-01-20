#pragma once

struct Sector
{
    double x;
    double y;
    double z;
    void update(double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    void print()
    {
        std::cout << "Sector(x:" << x << ", y:" << y << ", z:" << z << ")\n";
    }
    unsigned long seed()
    {
        return x * 0x3E5 + y * 0x2AB + z * 0x161;
    }
    glm::vec3 toPos(double mult) const
    {
        return glm::vec3(x * mult, y * mult, z * mult);
    }
    glm::vec3 toVec3() const
    {
        return glm::vec3(x, y, z);
    }
    void appendPos(double _x, double _y, double _z)
    {
        x += _x;
        y += _y;
        z += _z;
    }
    void mult(double mul)
    {
        x *= mul;
        y *= mul;
        z *= mul;
    }
    // std::ostream &operator<<(std::ostream &out, const Sector &s)
    // {
        // return out << "Sector(x:" << s.x << ",y:" << s.y << ", z:" << s.z;
    // }
    Sector operator+(const Sector &other)
    {
        Sector newSector;
        newSector.x = this->x + other.x;
        newSector.y = this->y + other.y;
        newSector.z = this->z + other.z;
        return newSector;
    }
    Sector operator-(const Sector &other)
    {
        Sector newSector;
        newSector.x = this->x - other.x;
        newSector.y = this->y - other.y;
        newSector.z = this->z - other.z;
        return newSector;
    }
};