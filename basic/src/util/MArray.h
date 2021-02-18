#pragma once

template <typename T>
struct MArray
{
    T *data = nullptr;
    size_t size;

    MArray<T>() : size(0) {}
    MArray<T>(size_t size_) { make_empty(size_); }
    ~MArray() { freePtr(); }
    void freePtr()
    {
        std::cout << "Freeing array pointer\n";
        free(data);
    }
    T *get() { return data; }
    void make_empty(size_t size_)
    {
        freePtr();
        data = (T *)malloc(size_ * sizeof(T));
        size = size_;
    }
    void transfer(const MArray &other)
    {
        data = other.data;
        size = other.size;
        other.data = nullptr;
    }
    void resize(size_t size_)
    {
        size_t minSize = std::min(size, size_);
        T *temp = (T *)malloc(size_ * sizeof(T));
        std::copy(&data[0], &data[0] + minSize, &temp[0]); // copy current data to temp
        data = temp;                                       // change data to temp
    }
    void insert(const T &val)
    {
        resize(size + 1);
        data[size - 1] = val;
    }
    T operator[](int i) const { return data[i]; }
};