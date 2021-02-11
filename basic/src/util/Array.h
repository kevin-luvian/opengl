#pragma once

template <typename T>
struct Array
{
    std::unique_ptr<T[]> data;
    size_t size;

    Array<T>() { size = 0; }
    Array<T>(size_t size_)
    {
        data = std::make_unique<T[]>(size_);
        size = size_;
    }
    T *get() const
    {
        return data.get();
    }
    void make_from(const Array<T> &other) { make_from(other.get(), other.size); }
    void make_from(const T *data_, const size_t size_)
    {
        if (size != size_)
        {
            data.reset(new T[size_]);
            size = size_;
        }
        std::copy(&data_[0], &data_[0] + size_, &data[0]);
    }
    void make_from(std::vector<T> vData)
    {
        size_t vSize = vData.size();
        if (size != vData.size()) // resource cannot be reused
        {
            data.reset(new T[vSize]);
            size = vSize;
        }
        std::copy(vData.begin(), vData.end(), &data[0]);
    }
    std::vector<T> make_to_vector()
    {
        std::vector<T> vData(size);
        std::copy(&data[0], &data[0] + size, vData.begin());
        return vData;
    }
    void release() { data.release(); }
    void transfer(Array<T> &other)
    {
        size = other.size;
        data = std::move(other.data);
    }
    void insert_array(Array<T> &other)
    {
        append(other, 0, other.size);
    }
    void append(Array<T> &other, int offset, int limit)
    {
        for (int i = 0; i < limit; i++)
        {
            data[offset + i] = other[i];
        }
    }
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << "(Array) [" << i << "]:" << data[i] << "\n";
        }
        std::cout << std::endl;
    }
    Array<T> copy() const
    {
        Array<T> res(size);
        std::copy(&data[0], &data[0] + size, &res[0]);
        return res;
    }
    size_t byte_size() const { return size * type_size(); }
    size_t type_size() const { return sizeof(T); }

    T operator[](int i) const { return data[i]; }
    T &operator[](int i) { return data[i]; }

    Array<T> &operator=(const Array<T> &other)
    {
        if (this != &other) // not a self-assignment
            make_from(other);
        return *this;
    }
};