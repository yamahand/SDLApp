#pragma once
#include <cstdint>

namespace lib {
/// @brief Interface for memory allocators
class MemoryAllocator {
public:
    MemoryAllocator() = default;
    MemoryAllocator(uintptr_t memoryAddress, size_t memorySize) : m_memoryAddress(memoryAddress), m_memorySize(memorySize) {}
    virtual ~MemoryAllocator() = default;

    virtual void* Allocate(size_t size) = 0;
    virtual void Deallocate(void* ptr) = 0;

    size_t GetMemorySize() const { return m_memorySize; }
    uintptr_t GetMemoryAddress() const { return m_memoryAddress; }

private:
    uintptr_t m_memoryAddress = 0;
    size_t m_memorySize = 0;
};
}