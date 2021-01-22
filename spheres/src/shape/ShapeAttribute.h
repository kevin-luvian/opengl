#pragma once

struct Vertex
{
    float x, y, z;
    friend std::ostream &operator<<(std::ostream &out, const Vertex &v)
    {
        out << "x:" << v.x << ", y:" << v.y << ", z:" << v.z;
        return out;
    }
};

struct Indice
{
    unsigned int top, left, right;
    friend std::ostream &operator<<(std::ostream &out, const Indice &t)
    {
        out << "top:" << t.top << ", left:" << t.left << ", right:" << t.right;
        return out;
    }
};

struct ShapeAttribute
{
    DetailedArray<Indice> indices;
    DetailedArray<Vertex> vertices;

    void release()
    {
        indices.release();
        vertices.release();
    }
    void PrintI()
    {
        for (unsigned int i = 0; i < indices.size; i++)
        {
            std::cout << "[" << i << "] " << indices[i] << "\n";
            if ((i + 1) % 4 == 0)
                std::cout << "\n";
        }
    }
};