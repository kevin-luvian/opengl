#pragma once

template <typename T>
struct DetailedArray
{
    std::unique_ptr<T[]> data;
    long size;

    T *get()
    {
        return data.get();
    }

    void make_empty(long size_)
    {
        data = std::make_unique<T[]>(size_);
        size = size_;
    }
    void make_from(const T *data_, long size_)
    {
        data = std::make_unique<T[]>(size_);
        size = size_;
        for (int i = 0; i < size_; i++)
        {
            data[i] = data_[i];
        }
    }
    void make_from(std::vector<T> vData)
    {
        data = std::make_unique<T[]>(vData.size());
        size = vData.size();
        for (int i = 0; i < size; i++)
        {
            data[i] = vData[i];
        }
    }
    std::vector<T> make_to_vector()
    {
        std::vector<T> vData;
        for (int i = 0; i < size; i++)
        {
            vData.push_back(data[i]);
        }
        return vData;
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
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << "(DetailedArray) [" << i << "]:" << data[i] << "\n";
        }
        std::cout << std::endl;
    }
    DetailedArray<T> copy() const
    {
        // return std::copy(data.get(), data.get() + size, data.get());
        DetailedArray<T> res;
        res.make_empty(size);
        for (int i = 0; i < size; i++)
        {
            res[i] = data[i];
        }
        return res;
    }

    long byte_size() { return size * type_size(); }
    long type_count() { return byte_size() / type_size(); }
    std::size_t type_size() { return sizeof(T); }

    T operator[](int i) const { return data[i]; }
    T &operator[](int i) { return data[i]; }
};