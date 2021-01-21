#pragma once

struct SphereAttribute
{
    DetailedArray<unsigned int> indices;
    DetailedArray<float> vertices;

    void release()
    {
        indices.release();
        vertices.release();
    }
    void PrintI()
    {
        for (unsigned int i = 0; i < indices.size; i++)
        {
            std::cout << "[" << i << "] " << indices.data[i] << ", ";
            if ((i + 1) % 4 == 0)
                std::cout << "\n";
        }
    }
};