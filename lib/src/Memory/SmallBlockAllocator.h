#pragma once

#include "Memory/MemoryAllocator.h"
#include <bitset>

namespace lib {

template<size_t BlockSize>
class SmallBlockAllocator : public MemoryAllocator {
public:
    SmallBlockAllocator(uintptr_t memoryAddress, size_t memorySize)
        : MemoryAllocator(memoryAddress, memorySize) {}

    void* Allocate(size_t size) override;
    void Deallocate(void* ptr) override;

    constexpr size_t GetBlockSize() const { return BlockSize; }

private:
    std::bitset<256> m_freeBlockBit;
};

}  // namespace lib