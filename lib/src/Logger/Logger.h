#pragma once

#include "Config/Config.h"
#include "Core/Singleton.h"


#if defined(PB_TRACE)
#define LOG_TRACE(category, ...) GetLogger().Trace(Logger::Level::Trace, category, __VA_ARGS__)
#define LOG_INFO(category, ...) GetLogger().Trace(Logger::Level::Info, category, __VA_ARGS__)
#define LOG_WARN(category, ...) GetLogger().Trace(Logger::Level::Warn, category, __VA_ARGS__)
#define LOG_ERROR(category, ...) GetLogger().Trace(Logger::Level::Error, category, __VA_ARGS__)
#else
#define LOG_TRACE(category, ...)
#define LOG_INFO(category, ...)
#define LOG_WARN(category, ...)
#define LOG_ERROR(category, ...)
#endif

namespace lib {

class Logger {
public:
	enum class Level {
		Trace,
		Info,
		Warn,
		Error,
	};
public:
    Logger() = default;
	~Logger() = default;

	void Initialize();
	void Finalize();

	void Trace(Level level, const char* category, const char* format, ...);
};

static Logger& GetLogger() {
	return Singleton<Logger>::GetInstance();
}

}  // namespace lib