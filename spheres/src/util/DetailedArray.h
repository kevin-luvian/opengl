#pragma once

template <typename T>
struct DetailedArray
{
    std::unique_ptr<T[]> data;
    long size;

    void make_empty(long size_)
    {
        data = std::make_unique<T[]>(size_);
        size = size_;
    }
    void release() { data.release(); }
    void insert(DetailedArray &other)
    {
        append(other, 0, other.size);
    }
    void append(DetailedArray &other, int offset, int limit)
    {
        for (int i = 0; i < limit; i++)
        {
            data[offset + i] = other[i];
        }
    }

    long byte_size() { return size * type_size(); }
    std::size_t type_size() { return sizeof(T); }

    T operator[](int i) const { return data[i]; }
    T &operator[](int i) { return data[i]; }
};
