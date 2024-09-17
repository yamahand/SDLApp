#include "Logger/Logger.h"

#include <array>
#include <cstdarg>
#include <cstdio>
#include <format>

#include "Logger/LogLevel.h"

namespace lib::log {

void Log(Level level, const char* category, const char* fileName, const char* functionName, int line, const std::string& str) {
    // ログメッセージのフォーマットと出力
    printf("%s\n", str.c_str());
}

void Log2(Level level, const char* category, const char* fileName, const char* functionName, int line, const std::string& str, const std::initializer_list<LogParameter>& params) {
    // ログメッセージのフォーマットと出力
    printf("%s\n", str.c_str());
}

void Logger::Initialize() {
    // 初期化コード
}

void Logger::Finalize() {
    // 終了コード
}

void Logger::Trace(Level level, const char* category, const char* format, ...) {
    // 可変引数を処理してログを出力
    va_list args;
    va_start(args, format);
    // ここで std::format を使用してフォーマットされた文字列を生成
    std::string formattedMessage = std::vformat(format, std::make_format_args(args));
    va_end(args);

    Log(level, category, __FILE__, __func__, __LINE__, formattedMessage);
}

class ToStringVisitor {
public:
    std::string operator()(int8_t value) const {
        return toString(value);
    }

    std::string operator()(int16_t value) const {
        return toString(value);
    }

    std::string operator()(int32_t value) const {
        return toString(value);
    }

    std::string operator()(int64_t value) const {
        return toString(value);
    }

    std::string operator()(uint8_t value) const {
        return toString(value);
    }

    std::string operator()(uint16_t value) const {
        return toString(value);
    }

    std::string operator()(uint32_t value) const {
        return toString(value);
    }

    std::string operator()(uint64_t value) const {
        return toString(value);
    }

    std::string operator()(float value) const {
        return toString(value);
    }

    std::string operator()(double value) const {
        return toString(value);
    }

    std::string operator()(bool value) const {
        return value ? "true" : "false";
    }

    std::string operator()(const char* value) const {
        return std::string(value);
    }

private:
    template <typename T>
    std::string toString(T value) const {
        std::array<char, 32> buffer;  // 十分なサイズのバッファを確保
        std::snprintf(buffer.data(), buffer.size(), "%g", static_cast<double>(value));
        return std::string(buffer.data());
    }
};

}  // namespace lib::log
