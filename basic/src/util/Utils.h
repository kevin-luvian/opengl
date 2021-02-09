#pragma once

namespace util
{
    static const float PI = 3.141592741f;

    // Utility function to calculate radian angles, overflow unsafe.
    static float toRadians(float degreeAngle) { return degreeAngle * PI / 180.0f; }

    // Utility function to calculate degree angles, overflow unsafe.
    static float toDegrees(float radianAngle) { return radianAngle * 180.0f / PI; }

    // Utility function to map value from a range to another range. Formula: Y = (X-A)/(B-A) * (D-C) + C
    static float mapBetweenFloat(float value, float from_start, float from_end, float to_start, float to_end)
    {
        return ((value - from_start) / (from_end - from_start) * (to_end - to_start)) + to_start;
    }

    // Utility function to get inverse square root using fast inverse square root algorithm
    static double fisqrt(double number)
    {
        double y = number;
        double x2 = y * 0.5;
        std::int64_t i = *(std::int64_t *)&y;
        // The magic number is for doubles is from https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
        i = 0x5fe6eb50c7b537a9 - (i >> 1);
        y = *(double *)&i;
        y = y * (1.5 - (x2 * y * y)); // 1st iteration
        //      y  = y * ( 1.5 - ( x2 * y * y ) );   // 2nd iteration, this can be removed
        return y;
    }

    static float clamp(float val, float min, float max)
    {
        return std::max(std::min(val, min), max);
    }

    static float min(float a, float b)
    {
        if (a < b)
            return a;
        return b;
    }

    static float min(float a, float b, float c)
    {
        return min(a, min(b, c));
    }
} // namespace util