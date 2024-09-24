#pragma once

namespace lib {

enum class AllocatorType {
    Single,
    Double,
    Stack,
    Pool,

    Default,
    Custom,
};

constexpr size_t KiB = 1024;
constexpr size_t MiB = 1024 * KiB;
constexpr size_t GiB = 1024 * MiB;

// バイトをキビバイトに変換する関数
inline constexpr size_t toKiB(size_t bytes) {
    return bytes / KiB;
}
// メビバイトに変換する関数
inline constexpr size_t toMiB(size_t bytes) {
    return bytes / MiB;
}
// ギビバイトに変換する関数
inline constexpr size_t toGiB(size_t bytes) {
    return bytes / GiB;
}

inline void* operator new (size_t size, size_t aligment, AllocatorType type) {
    return ::operator new (size);
}

inline void* operator new (size_t size, size_t aligment, AllocatorType type, const char* file, int line) {
    return ::operator new (size, aligment, type);
}


} // namespace lib