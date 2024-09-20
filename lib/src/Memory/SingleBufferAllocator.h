#pragma once

#include "Memory/MemoryAllocator.h"

namespace lib {

class SingleBufferAllocator : public MemoryAllocator {
public:
    SingleBufferAllocator(const SingleBufferAllocator&) = delete;
    SingleBufferAllocator& operator=(const SingleBufferAllocator&) = delete;
    SingleBufferAllocator(uintptr_t memoryAddress, size_t memorySize) : MemoryAllocator(memoryAddress, memorySize) {}
    virtual ~SingleBufferAllocator() = default;

    void* Allocate(size_t size) override {
        if (size + m_currentAddress > GetMemorySize()) {
            return nullptr;
        }

        const auto currentAddress = m_currentAddress;
        m_currentAddress += size;
        return reinterpret_cast<void*>(GetMemoryAddress() + currentAddress);
    }

    void Deallocate(void* ptr) override {
        // Do nothing
    }

    void Reset() {
        m_currentAddress = 0;
    }

private:
    uintptr_t m_currentAddress = 0;
};

} // namespace lib