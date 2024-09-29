#pragma once

#include <new>

// 標準のoperator new
void* operator new(size_t size);

// 配列用のoperator new[]
void* operator new[](size_t size);

// 例外を投げないoperator new
void* operator new(size_t size, const std::nothrow_t&) noexcept;

// 配列用の例外を投げないoperator new[]
void* operator new[](size_t size, const std::nothrow_t&) noexcept;

// 配置new（Placement new）
void* operator new(size_t size, void* ptr) noexcept;

// 配列用の配置new（Placement new）
void* operator new[](size_t size, void* ptr) noexcept;

// アライメントを指定したoperator new
void* operator new(size_t size, std::align_val_t alignment);

// アライメントを指定した配列用のoperator new[]
void* operator new[](size_t size, std::align_val_t alignment);

// アライメントを指定し、例外を投げないoperator new
void* operator new(size_t size, std::align_val_t alignment, const std::nothrow_t&) noexcept;

// アライメントを指定し、例外を投げない配列用のoperator new[]
void* operator new[](size_t size, std::align_val_t alignment, const std::nothrow_t&) noexcept;

// 標準のoperator delete
void operator delete(void* ptr) noexcept;

// 配列用のoperator delete[]
void operator delete[](void* ptr) noexcept;

// サイズ指定のoperator delete
void operator delete(void* ptr, size_t size) noexcept;

// サイズ指定の配列用のoperator delete[]
void operator delete[](void* ptr, size_t size) noexcept;

// 例外を投げないoperator delete
void operator delete(void* ptr, const std::nothrow_t&) noexcept;

// 例外を投げない配列用のoperator delete[]
void operator delete[](void* ptr, const std::nothrow_t&) noexcept;

// 配置delete（Placement delete）
void operator delete(void* ptr, void* place) noexcept;

// 配列用の配置delete（Placement delete）
void operator delete[](void* ptr, void* place) noexcept;

// アライメントを指定したoperator delete
void operator delete(void* ptr, std::align_val_t alignment) noexcept;

// アライメントを指定した配列用のoperator delete[]
void operator delete[](void* ptr, std::align_val_t alignment) noexcept;

// アライメントとサイズを指定したoperator delete
void operator delete(void* ptr, size_t size, std::align_val_t alignment) noexcept;

// アライメントとサイズを指定した配列用のoperator delete[]
void operator delete[](void* ptr, size_t size, std::align_val_t alignment) noexcept;
