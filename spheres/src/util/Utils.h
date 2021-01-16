#pragma once

namespace util
{
    static const float PI = 3.141592741f;

    // Utility function to calculate radian angles, overflow safe.
    static float toRadians(float degreeAngle)
    {
        return std::fmod((degreeAngle * PI / 180.0f), 2 * PI);
    }

    // Utility function to calculate degree angles, overflow safe.
    static float toDegrees(float radianAngle)
    {
        return std::fmod((radianAngle * 180.0f / PI), 360.0f);
    }

    static float mapBetweenFloat(float value, float from_start, float from_end, float to_start, float to_end)
    {
        // Y = (X-A)/(B-A) * (D-C) + C
        return ((value - from_start) / (from_end - from_start) * (to_end - to_start)) + to_start;
    }
} // namespace util