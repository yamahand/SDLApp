#pragma once

#include <format>
#include <string>
#include <variant>

#include "Config/Config.h"
#include "Core/Singleton.h"

#if defined(PB_TRACE)
#define __LOG(level, category, fmt, ...) lib::log::Log(level, category, __FILE__, __func__, __LINE__, std::format(fmt __VA_OPT__(, ) __VA_ARGS__));

#define LOG_TRACE(category, ...) __LOG(::lib::log::Level::Trace, category, __VA_ARGS__)
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

enum class Level;

using LogParameter = std::variant<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, float, double, bool, const char*>;

void Log(Level level, const char* category, const char* fileName, const char* functionName, int line, const std::string& str);

class Logger {
    friend class Singleton<Logger>;
    Logger()  = default;
    ~Logger() = default;

public:
    void Initialize();
    void Finalize();

    void Trace(Level level, const char* category, const char* format, ...);
};

Logger& GetLogger();

}  // namespace lib::log
