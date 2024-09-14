#include "Logger/Logger.h"

#include <cstdarg>

namespace lib {
void Logger::Initialize() {
}
void Logger::Finalize() {
}
void Logger::Trace(Level level, const char* category, const char* format, ...) {
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}
}  // namespace lib
