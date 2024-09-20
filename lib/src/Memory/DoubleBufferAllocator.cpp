#include "Memory/DoubleBufferAllocator.h"

namespace lib {

DoubleBufferAllocator::DoubleBufferAllocator(uintptr_t memoryAddress, size_t memorySize)
    : m_allocators{SingleBufferAllocator(memoryAddress, memorySize / 2), SingleBufferAllocator(memoryAddress + memorySize / 2, memorySize / 2)} {
}

void* DoubleBufferAllocator::Allocate(size_t size) {
    return m_allocators[m_currentIndex].Allocate(size);
}

void DoubleBufferAllocator::Deallocate(void* ptr) {
    m_allocators[m_currentIndex].Deallocate(ptr);
}

void DoubleBufferAllocator::Reset() {
    m_currentIndex = 1 - m_currentIndex;
    m_allocators[m_currentIndex].Reset();
}

}  // namespace lib
