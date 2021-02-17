#pragma once

template <typename T>
struct Array
{
    std::unique_ptr<T[]> data;
    size_t size;

    Array<T>() : size(0) {}
    Array<T>(size_t size_) { make_empty(size_); }
    Array<T>(const Array<T> &arr) { make_from(arr); }
    T *get() const { return data.get(); }
    void copy_to(T *ptr) const { std::copy(&data[0], &data[0] + size, ptr); }
    void make_fill(size_t size_, const T &sample)
    {
        make_empty(size_);
        std::fill(&data[0], &data[0] + size, sample);
    }
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
    std::vector<T> make_to_vector() const
    {
        std::vector<T> vData(size);
        copy_to(vData.begin());
        return vData;
    }
    void append(const Array<T> &other)
    {
        size_t currentSize = size;
        resize(size + other.size);         // resize array to fit other
        other.copy_to(&data[currentSize]); // copy new data
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
        Array<T> temp(size_);
        std::copy(&data[0], &data[0] + minSize, &temp[0]); // copy current data to temp
        transfer(temp);                                    // change data to temp
    }
    void print(unsigned int limit) const
    {
        std::cout << "Array(\n";
        for (int i = 0; i < size; i++)
        {
            std::cout << "[" << i << "]:" << data[i] << ", ";
            if (limit == (i + 1))
                std::cout << "\n";
        }
        std::cout << ")\n";
    }
    size_t byte_size() const { return size * type_size(); }
    size_t type_size() const { return sizeof(T); }

    T operator[](int i) const { return data[i]; }
    T &operator[](int i) { return data[i]; }

    void operator=(const Array<T> &other)
    {
        if (this != &other) // not a self-assignment
            make_from(other);
    }
};