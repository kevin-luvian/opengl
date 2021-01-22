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
    static double invsqrtQuake( double number )
    {
        double y = number;
        double x2 = y * 0.5;
        std::int64_t i = *(std::int64_t *) &y;
        // The magic number is for doubles is from https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
        i = 0x5fe6eb50c7b537a9 - (i >> 1);
        y = *(double *) &i;
        y = y * (1.5 - (x2 * y * y));   // 1st iteration
        //      y  = y * ( 1.5 - ( x2 * y * y ) );   // 2nd iteration, this can be removed
        return y;
    }
} // namespace util