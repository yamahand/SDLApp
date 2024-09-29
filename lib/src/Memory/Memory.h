#pragma once

#include <new>

#undef PB_NEW
#if defined(PB_MEMORY_DEBUG)
#define PB_NEW(size) new(size, __FILE__, __LINE__)
#define PB_NEW_ALIGN(size, align) new(size, align, __FILE__, __LINE__)
#else
#define PB_NEW(size) new(size, nullptr, 0)
#define PB_NEW(size, align) new(size, align, nullptr, 0)
#endif // PB_MEMORY_DEBUG

// メモリ確保関数
void* operator new(size_t size, const char* fileName, size_t line) noexcept;

// アライメントを指定したメモリ確保関数
void* operator new(size_t size, std::align_val_t aligment, const char* fileName, size_t line) noexcept;

namespace lib {

constexpr size_t KiB = 1024;
constexpr size_t MiB = 1024 * KiB;
constexpr size_t GiB = 1024 * MiB;

// バイトをキビバイトに変換する関数
inline constexpr size_t toKiB(size_t bytes) {
    return bytes * KiB;
}
// バイトをメビバイトに変換する関数
inline constexpr size_t toMiB(size_t bytes) {
    return bytes * MiB;
}
// バイトをギビバイトに変換する関数
inline constexpr size_t toGiB(size_t bytes) {
    return bytes * GiB;
}

} // namespace lib
