#include "Memory/Memory.h"
#include "Memory/NewDeleteOverride.h"

// メモリ確保関数
void* operator new(size_t size, const char* fileName, size_t line) noexcept {
    return malloc(size);
}

// アライメントを指定したメモリ確保関数
void* operator new(size_t size, std::align_val_t aligment, const char* fileName, size_t line) noexcept {
    return _aligned_malloc(size, static_cast<size_t>(aligment));
}

