#pragma once

#include <format>
#include <string>
#include <variant>

#include "Config/Config.h"
#include "Core/Singleton.h"

#if defined(PB_TRACE)

#include <format>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace lib::log {

// カスタムアロケータの定義
template <typename T>
struct LoggerAllocator {
    using value_type = T;

    LoggerAllocator() = default;

    template <typename U>
    constexpr LoggerAllocator(const LoggerAllocator<U>&) noexcept {
    }

    T* allocate(std::size_t n) {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) noexcept {
        ::operator delete(p);
    }
};

template <typename T, typename U>
bool operator==(const LoggerAllocator<T>&, const LoggerAllocator<U>&) {
    return true;
}

template <typename T, typename U>
bool operator!=(const LoggerAllocator<T>&, const LoggerAllocator<U>&) {
    return false;
}

using CustomString = std::basic_string<char, std::char_traits<char>, LoggerAllocator<char>>;
}  // namespace lib::log

#define __LOG(level, category, fmt, ...)                                                    \
    {                                                                                       \
        lib::log::CustomString customString;                                                \
        std::format_to(std::back_inserter(customString), fmt __VA_OPT__(, ) __VA_ARGS__);   \
        lib::log::Log(level, category, __FILE__, __func__, __LINE__, customString.c_str()); \
    }
#define __LOG2(level, category, fmt, ...)                                                                   \
    {                                                                                                       \
        lib::log::CustomString customString;                                                                \
        std::format_to(std::back_inserter(customString), fmt __VA_OPT__(, ) __VA_ARGS__);                   \
        lib::log::Log2(level, category, __FILE__, __func__, __LINE__, customString.c_str(), {__VA_ARGS__}); \
    }

#define LOG_TRACE(category, ...) __LOG2(::lib::log::Level::Trace, category, __VA_ARGS__)
#define LOG_INFO(category, ...) __LOG(lib::log::Level::Info, category, __VA_ARGS__)
#define LOG_WARN(category, ...) __LOG(lib::log::Level::Warn, category, __VA_ARGS__)
#define LOG_ERROR(category, ...) __LOG(lib::log::Level::Error, category, __VA_ARGS__)
#else
#define LOG_TRACE(category, ...)
#define LOG_INFO(category, ...)
#define LOG_WARN(category, ...)
#define LOG_ERROR(category, ...)
#endif

namespace lib::log {

static void test() {
    lib::log::CustomString customString;
    std::format_to(std::back_inserter(customString), "test");
}

enum class Level;

using LogParameter = std::variant<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, float, double, bool, const char*>;

void Log(Level level, const char* category, const char* fileName, const char* functionName, int line, const std::string& str);
void Log2(Level level, const char* category, const char* fileName, const char* functionName, int line, const std::string& str, const std::initializer_list<LogParameter>& params);

class Logger {
    friend class Singleton<Logger>;
    Logger()  = default;
    ~Logger() = default;

public:
    void Initialize();
    void Finalize();

    void Trace(Level level, const char* category, const char* format, ...);
};

static Logger& GetLogger() {
    return Singleton<Logger>::GetInstance();
}

}  // namespace lib::log
