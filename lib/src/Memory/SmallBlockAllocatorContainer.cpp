#include "SmallBlockAllocatorContainer.h"

namespace lib {
SmallBlockAllocatorContainer::SmallBlockAllocatorContainer(uintptr_t memoryAddress, size_t memorySize)
    : MemoryAllocator(memoryAddress, memorySize) {
    m_smallBlockAllocator32  = SmallBlockAllocator<32>(memoryAddress, memorySize);
    m_smallBlockAllocator48  = SmallBlockAllocator<48>(memoryAddress, memorySize);
    m_smallBlockAllocator64  = SmallBlockAllocator<64>(memoryAddress, memorySize);
    m_smallBlockAllocator96  = SmallBlockAllocator<96>(memoryAddress, memorySize);
    m_smallBlockAllocator128 = SmallBlockAllocator<128>(memoryAddress, memorySize);
    m_smallBlockAllocator192 = SmallBlockAllocator<192>(memoryAddress, memorySize);
    m_smallBlockAllocator256 = SmallBlockAllocator<256>(memoryAddress, memorySize);
}

void* SmallBlockAllocatorContainer::Allocate(size_t size) {
    if (size <= 32) {
        return m_smallBlockAllocator32.Allocate(size);
    } else if (size <= 48) {
        return m_smallBlockAllocator48.Allocate(size);
    } else if (size <= 64) {
        return m_smallBlockAllocator64.Allocate(size);
    } else if (size <= 96) {
        return m_smallBlockAllocator96.Allocate(size);
    } else if (size <= 128) {
        return m_smallBlockAllocator128.Allocate(size);
    } else if (size <= 192) {
        return m_smallBlockAllocator192.Allocate(size);
    } else if (size <= 256) {
        return m_smallBlockAllocator256.Allocate(size);
    } else {
        return nullptr;
    }
    return nullptr;
}

void SmallBlockAllocatorContainer::Deallocate(void* ptr) {
}

}  // namespace lib
