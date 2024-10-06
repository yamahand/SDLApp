#pragma once
#include <cstdint>

#include "Core/Assert.h"

namespace lib {
/// @brief Interface for memory allocators
class MemoryAllocator {
public:
    MemoryAllocator() = default;
    MemoryAllocator(uintptr_t memoryAddress, size_t memorySize)
        : m_memoryAddress(memoryAddress), m_memorySize(memorySize) {
    }
    virtual ~MemoryAllocator() = default;

    void Initialize(uintptr_t memoryAddress, size_t memorySize) {
        PB_ASSERT_MSG(!IsInitialized(), "lib.allocator", "MemoryAllocator is Initialized." );
        m_memoryAddress = memoryAddress;
        m_memorySize    = memorySize;
    }

    bool IsInitialized() const {
        return m_memoryAddress != 0 && m_memorySize != 0;
    }

    void Finalize() {
        m_memoryAddress = 0;
        m_memorySize    = 0;
    }

    virtual void* Allocate(size_t size) = 0;
    virtual void Deallocate(void* ptr)  = 0;

    size_t GetMemorySize() const {
        return m_memorySize;
    }
    uintptr_t GetMemoryAddress() const {
        return m_memoryAddress;
    }

private:
    uintptr_t m_memoryAddress = 0;
    size_t m_memorySize       = 0;
};
}  // namespace lib
