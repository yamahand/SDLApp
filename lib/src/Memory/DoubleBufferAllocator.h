#pragma once
#include <array>

#include "Memory/MemoryAllocator.h"
#include "Memory/SingleBufferAllocator.h"


namespace lib {

class DoubleBufferAllocator : public MemoryAllocator {
public:
    DoubleBufferAllocator(const DoubleBufferAllocator&) = delete;
    DoubleBufferAllocator& operator=(const DoubleBufferAllocator&) = delete;
    DoubleBufferAllocator(uintptr_t memoryAddress, size_t memorySize);
    virtual ~DoubleBufferAllocator() = default;

    void* Allocate(size_t size) override;

    void Deallocate(void* ptr) override;

    void Reset();

private:
    std::array<SingleBufferAllocator, 2> m_allocators;
    uint32_t m_currentIndex = 0;
};

} // namespace lib