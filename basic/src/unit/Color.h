#pragma once

#include <assimp/color4.h>

namespace unit
{
    struct color
    {
        float r, g, b, a;

        color(float r_, float g_, float b_, float a_) : r(r_), g(g_), b(b_), a(a_) {}
        color(const unit::vec4 &v) : r(v.x), g(v.y), b(v.z), a(v.w) {}
        color(const aiColor4D &c) : r(c.r), g(c.g), b(c.b), a(c.a) {}

        std::string hash() const
        {
            return std::to_string(int(r * 100)) +
                   std::to_string(int(g * 100)) +
                   std::to_string(int(b * 100)) +
                   std::to_string(int(a * 100));
        }
        void clamp()
        {
            r = util::clamp(r, 0.0f, 1.0f);
            g = util::clamp(g, 0.0f, 1.0f);
            b = util::clamp(b, 0.0f, 1.0f);
            a = util::clamp(a, 0.0f, 1.0f);
        }
        color operator-() const { return {-r, -g, -b, -a}; }
        color operator-(const color &o) const { return *this + (-o); }
        void operator-=(const color &o) { *this = *this - o; }
        color operator+(const color &o) const { return {r + o.r, g + o.g, b + o.b, a + o.a}; }
        void operator+=(const color &o) { *this = *this + o; }
        void operator*=(const float &val)
        {
            r *= val;
            g *= val;
            b *= val;
            a *= val;
        }
        bool operator==(const color &o) const { return r == o.r && g == o.g && b == o.b && a == o.a; }
        friend std::ostream &operator<<(std::ostream &out, const color &col)
        {
            out << "r:" << col.r << ", g:" << col.g << ", b:" << col.b << ", a:" << col.a;
            return out;
        }
    };
    static color clamp(const color &col)
    {
        color res = col;
        res.clamp();
        return res;
    }
} // namespace unit

namespace Colors
{
    static const unit::color BLACK = {0.0f, 0.0f, 0.0f, 1.0f};
    static const unit::color WHITE = {1.0f, 1.0f, 1.0f, 1.0f};
    static const unit::color OCEAN = {0.0f, 0.4f, 0.7f, 1.0f};
} // namespace Colors
