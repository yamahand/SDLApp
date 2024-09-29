#include "Memory/Memory.h"

#include <cstdlib>
#include <vcruntime_new.h>

// 標準のoperator new
void* operator new(size_t size) {
    if (void* ptr = std::malloc(size)) {
        return ptr;
    }
    throw std::bad_alloc();
}

// 配列用のoperator new[]
void* operator new[](size_t size) {
    if (void* ptr = std::malloc(size)) {
        return ptr;
    }
    throw std::bad_alloc();
}

// 例外を投げないoperator new
void* operator new(size_t size, const std::nothrow_t&) noexcept {
    return std::malloc(size);
}

// 配列用の例外を投げないoperator new[]
void* operator new[](size_t size, const std::nothrow_t&) noexcept {
    return std::malloc(size);
}

// アライメントを指定したoperator new
void* operator new(size_t size, std::align_val_t alignment) {
    if (void* ptr = _aligned_malloc(static_cast<size_t>(alignment), size)) {
        return ptr;
    }
    throw std::bad_alloc();
}

// アライメントを指定した配列用のoperator new[]
void* operator new[](size_t size, std::align_val_t alignment) {
    if (void* ptr = _aligned_malloc(static_cast<size_t>(alignment), size)) {
        return ptr;
    }
    throw std::bad_alloc();
}

// アライメントを指定し、例外を投げないoperator new
void* operator new(size_t size, std::align_val_t alignment, const std::nothrow_t&) noexcept {
    return _aligned_malloc(static_cast<size_t>(alignment), size);
}

// アライメントを指定し、例外を投げない配列用のoperator new[]
void* operator new[](size_t size, std::align_val_t alignment, const std::nothrow_t&) noexcept {
    return _aligned_malloc(static_cast<size_t>(alignment), size);
}

// 標準のoperator delete
void operator delete(void* ptr) noexcept {
    std::free(ptr);
}

// 配列用のoperator delete[]
void operator delete[](void* ptr) noexcept {
    std::free(ptr);
}

// サイズ指定のoperator delete
void operator delete(void* ptr, size_t size) noexcept {
    std::free(ptr);
}

// サイズ指定の配列用のoperator delete[]
void operator delete[](void* ptr, size_t size) noexcept {
    std::free(ptr);
}

// 例外を投げないoperator delete
void operator delete(void* ptr, const std::nothrow_t&) noexcept {
    std::free(ptr);
}

// 例外を投げない配列用のoperator delete[]
void operator delete[](void* ptr, const std::nothrow_t&) noexcept {
    std::free(ptr);
}

// アライメントを指定したoperator delete
void operator delete(void* ptr, std::align_val_t alignment) noexcept {
    std::free(ptr);
}

// アライメントを指定した配列用のoperator delete[]
void operator delete[](void* ptr, std::align_val_t alignment) noexcept {
    std::free(ptr);
}

// アライメントとサイズを指定したoperator delete
void operator delete(void* ptr, size_t size, std::align_val_t alignment) noexcept {
    std::free(ptr);
}

// アライメントとサイズを指定した配列用のoperator delete[]
void operator delete[](void* ptr, size_t size, std::align_val_t alignment) noexcept {
    std::free(ptr);
}
