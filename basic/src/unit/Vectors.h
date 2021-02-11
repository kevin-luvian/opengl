#pragma once

namespace unit
{
    struct vec2
    {
        float x, y;
        vec2(float val) : x(val), y(val) {}
        vec2(float x_, float y_) : x(x_), y(y_) {}
        friend std::ostream &operator<<(std::ostream &out, const vec2 &v)
        {
            out << "x:" << v.x << ", y:" << v.y;
            return out;
        }
    };
    struct vec3
    {
        float x, y, z;
        vec3() { x = y = z = 0.0f; }
        vec3(float val) { x = y = z = val; }
        vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
        vec3 &scale(const float &val)
        {
            x *= val;
            y *= val;
            z *= val;
            return *this;
        }
        glm::vec3 toGLMVec3() { return glm::vec3(x, y, z); }
        float iLength() { return util::fisqrt(x * x + y * y + z * z); }
        void normalize() { scale(iLength()); }
        vec3 &add(const vec3 &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }
        vec3 &sub(const vec3 &other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }
        vec3 operator-(const vec3 &other) const
        {
            vec3 res = *this;
            return res.sub(other);
        }
        vec3 operator+(const vec3 &other) const
        {
            vec3 res = *this;
            return res.add(other);
        }
        vec3 &operator+=(const vec3 &other) { return add(other); }
        friend std::ostream &operator<<(std::ostream &out, const vec3 &v)
        {
            out << "x:" << v.x << ", y:" << v.y << ", z:" << v.z;
            return out;
        }
    };
    struct vec4
    {
        float x, y, z, w;
        vec4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
        vec4(float val) { x = y = z = w = val; }
    };
    static vec3 normalize(const vec3 &vector)
    {
        vec3 res = vector;
        res.normalize();
        return res;
    }
    static vec3 cross(const vec3 &v1, const vec3 &v2)
    {
        vec3 res;
        res.x = v1.y * v2.z - v1.z * v2.y;
        res.y = v1.z * v2.x - v1.x * v2.z;
        res.z = v1.x * v2.y - v1.y * v2.x;
        return res;
    }
} // namespace unit
