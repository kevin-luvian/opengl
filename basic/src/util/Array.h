#pragma once

template <typename T>
struct Array
{
    std::unique_ptr<T[]> data;
    size_t size;

    Array<T>() { size = 0; }
    Array<T>(size_t size_) { make_empty(size_); }
    T *get() const { return data.get(); }
    void make_empty(size_t size_)
    {
        data.reset(new T[size_]);
        size = size_;
    }
    void make_from(const Array<T> &other) { make_from(other.get(), other.size); }
    void make_from(const T *data_, const size_t &size_)
    {
        if (size != size_)
            make_empty(size_);
        std::copy(&data_[0], &data_[0] + size_, &data[0]);
    }
    void make_from(const std::vector<T> &vData)
    {
        size_t vSize = vData.size();
        if (size != vSize) // resource cannot be reused
            make_empty(vSize);
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
    void resize(size_t size_)
    {
        size_t minSize = std::min(size, size_);
        Array<T> temp = copy();
        make_empty(size_);
        std::copy(&temp.data[0], &temp.data[0] + minSize, &data[0]);
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

    void operator=(const Array<T> &other)
    {
        if (this != &other) // not a self-assignment
            make_from(other);
        // return *this;
    }
};