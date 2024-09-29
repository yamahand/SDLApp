#pragma once

#include "Memory/SmallBlockAllocator.h"

namespace lib {

class SmallBlockAllocatorContainer : public MemoryAllocator {
public:
    SmallBlockAllocatorContainer() = delete;

private:
SmallBlockAllocator<32> m_smallBlockAllocator32;
SmallBlockAllocator<48> m_smallBlockAllocator48;
SmallBlockAllocator<64> m_smallBlockAllocator64;
SmallBlockAllocator<96> m_smallBlockAllocator96;
SmallBlockAllocator<128> m_smallBlockAllocator128;
SmallBlockAllocator<192> m_smallBlockAllocator192;
SmallBlockAllocator<256> m_smallBlockAllocator256;

};

} // namespace lib