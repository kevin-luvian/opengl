#pragma once

namespace unit
{
    struct color
    {
        float r, g, b, a;

        color(float r_, float g_, float b_, float a_) : r(r_), g(g_), b(b_), a(a_) {}
        glm::vec4 toGLMVec4() const { return glm::vec4(r, g, b, a); }
        unit::vec4 toVec4() const { return unit::vec4(r, g, b, a); }
    };
    static color clamp(const color &col)
    {
        color res = col;
        res.r = util::clamp(col.r, 0.0f, 1.0f);
        res.g = util::clamp(col.g, 0.0f, 1.0f);
        res.b = util::clamp(col.b, 0.0f, 1.0f);
        res.a = util::clamp(col.a, 0.0f, 1.0f);
        return res;
    }
} // namespace unit

namespace Colors
{
    static const unit::color BLACK = {0.0f, 0.0f, 0.0f, 1.0f};
    static const unit::color WHITE = {1.0f, 1.0f, 1.0f, 1.0f};
} // namespace Colors
