#pragma once

namespace util
{
    static const float PI = 3.141592741f;

    // Utility function to calculate radian angles.
    static float toRadians(float degreeAngle)
    {
        return degreeAngle * PI / 180.0f;
    }

    // Utility function to calculate degree angles.
    static float toDegrees(float radianAngle)
    {
        return radianAngle * 180.0f / PI;
    }

    static float mapBetweenFloat(float value, float from_start, float from_end, float to_start, float to_end)
    {
        // Y = (X-A)/(B-A) * (D-C) + C
        return ((value - from_start) / (from_end - from_start) * (to_end - to_start)) + to_start;
    }

    static void fps()
    {
        static float fps = 0.0f;
        static float before = 0.0f;
        static char strFPS[20] = {0};
        float now = glfwGetTime();

        ++fps;

        if (now - before > 1.0f)
        {
            std::cout << strFPS << " FPS: " << int(fps) << "\n";
            before = now;
            fps = 0.0f;
        }
    }

    template <typename T>
    static void printArr(T *arr, unsigned int arr_count)
    {
        if (!arr)
            return;

        std::cout << "\nArr::\n";
        for (int i = 0; i < arr_count; i++)
        {
            std::cout << "[" << i << "]: " << arr[i] << ", ";
            if ((i + 1) % 3 == 0)
            {
                std::cout << "\n";
                if ((i + 1) % 4 == 0)
                    std::cout << "\n";
            }
        }
        std::cout << "\n";
    }

    static void printV3(glm::vec3 *arr, unsigned int arr_count)
    {
        if (!arr)
            return;

        std::cout << "\nArr::\n";
        for (int i = 0; i < arr_count; i++)
        {
            std::cout << "[" << i << "]:{x:" << arr[i].x << ",y:" << arr[i].y << ",z:" << arr[i].z << "}, ";
            if ((i + 1) % 3 == 0)
            {
                std::cout << "\n";
                if ((i + 1) % 4 == 0)
                    std::cout << "\n";
            }
        }
        std::cout << "\n";
    }

    static long DivideLong(long value, long divider)
    {
        long res = value / divider;
        if (std::abs(value) % divider > divider / 2)
        {
            if (value < 0)
                res -= 1;
            else
                res += 1;
        }
        return res;
    }
} // namespace util