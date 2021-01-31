#pragma once

#include <chrono>
#include <functional>
#include <fstream>
#include <thread>
#include <mutex>

#define PROFILING 1
#if PROFILING
#define BENCHMARK_PROFILE() BENCHMARK_PROFILE_NAME(__PRETTY_FUNCTION__)
#define BENCHMARK_PROFILE_NAME(name) Timer timer(name)
#else
#define BENCHMARK_PROFILE()
#define BENCHMARK_PROFILE_NAME(name)
#endif

struct BenchmarkResponse
{
    std::thread::id thread_id;
    std::string name;
    int64_t start_time, elapsed_time;
};

class Benchmark
{
private:
    std::mutex file_mutex;
    std::ofstream file;
    std::string category, filepath;
    int64_t isFirst = true;

    void writeHeader()
    {
        file.open(filepath);
        if (!file)
            std::cout << "File is not created!\n";
        file << "{\"otherData\":{},\"traceEvents\":[\n";
        // file.flush();
    }
    void writeFooter()
    {
        file << "]}";
        file.close();
    }

public:
    static Benchmark &Get()
    {
        static Benchmark *instance = new Benchmark();
        return *instance;
    }
    void begin(const std::string &_category, const std::string &_filepath = "../res/benchmark.json")
    {
        category = _category;
        filepath = _filepath;
        writeHeader();
    }
    void end() { writeFooter(); }
    void setCategory(const std::string &_category)
    {
        category = _category;
    }
    void write(BenchmarkResponse &response)
    {
        file_mutex.lock();
        if (!isFirst)
            file << ",\n";
        else
            isFirst = false;
        // std::cout << file.is_open() << std::endl;
        file << "{\"cat\":\"" << category << "\","
             << "\"dur\":" << response.elapsed_time << ","
             << "\"pid\":0,"
             << "\"tid\":" << response.thread_id << ","
             << "\"ts\":" << response.start_time << ","
             << "\"ph\":\"X\","
             << "\"name\":\"" << response.name << "\","
             << "\"args\":{}}";
        file.flush();
        file_mutex.unlock();
    }
};

class Timer
{
private:
    std::chrono::_V2::system_clock::time_point m_start_time;
    const char *name;

public:
    Timer(const char *_name)
    {
        name = _name;
        start();
    }
    ~Timer() { stop(); }

    void start()
    {
        m_start_time = std::chrono::high_resolution_clock::now();
    }
    void stop()
    {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto start_time = std::chrono::duration_cast<std::chrono::microseconds>(m_start_time.time_since_epoch());
        auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - m_start_time);
        BenchmarkResponse res = {
            std::this_thread::get_id(),
            name,
            start_time.count(),
            elapsed_time.count()};
        Benchmark::Get().write(res);
    }
};