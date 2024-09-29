#pragma once

#include <bitset>

#include "Memory/Memory.h"
#include "Memory/MemoryAllocator.h"

namespace lib {

template <size_t BlockSize>
class SmallBlockAllocator : public MemoryAllocator {
    static_assert(BlockSize >= sizeof(void*), "BlockSize must be greater than or equal to sizeof(void*)");
    static_assert(BlockSize % 16 == 0, "BlockSize must be a multiple of 16");

public:
    static constexpr size_t NeedMemorySize = toMiB(8);
    static constexpr size_t PageSize       = toKiB(4);

private:
    struct PageHeader {
        std::bitset<256> freeBlockBit;
    };
    constexpr static size_t PageHeaderSize = sizeof(PageHeader);

public:
    SmallBlockAllocator(uintptr_t memoryAddress, size_t memorySize)
        : MemoryAllocator(memoryAddress, memorySize) {
        assert(memorySize == NeedMemorySize);
        _Initialize();
    }

    void* Allocate(size_t size) override {
        if (size > BlockSize) {
            return nullptr;
        }

        for (size_t i = 0; i < GetPageCount(); ++i) {
            PageHeader* pageHeader = _GetPageHeader(i);
            size_t blockIndex      = _GetFirstFreeBlockIndex(pageHeader);
            if (blockIndex != pageHeader->freeBlockBit.size()) {
                return _Allocate(i, blockIndex);
            }
        }

        return nullptr;
    }
    void Deallocate(void* ptr) override {
        size_t pageIndex  = _GetPageIndex(ptr);
        size_t blockIndex = _GetBlockIndex(ptr);
        _Deallocate(pageIndex, blockIndex);
    }

    constexpr size_t GetBlockSize() const {
        return BlockSize;
    }
    constexpr size_t GetBlockCount() const {
        return PageSize / BlockSize;
    }
    constexpr size_t GetPageCount() const {
        return NeedMemorySize / PageSize;
    }

private:
    void _Initialize() {
        // BlockSizeがPageHeaderより小さいか
        bool isBlockSizeLessThanPageHeader = BlockSize < PageHeaderSize;

        // PageHeaderのサイズを格納するために必要なブロック数
        size_t needBlockCountForPageHeader = PageHeaderSize / BlockSize + (PageHeaderSize % BlockSize != 0);

        for (size_t i = 0; i < GetPageCount(); ++i) {
            PageHeader* pageHeader = _GetPageHeader(i);
            pageHeader->freeBlockBit.reset();

            // PageHeaderのサイズを格納するためのブロックを使用済みにする
            for (size_t j = 0; j < needBlockCountForPageHeader; ++j) {
                pageHeader->freeBlockBit.set(j);
            }
        }
    }
    void* _Allocate(size_t pageIndex, size_t blockIndex) {
        uintptr_t pageAddress  = GetMemoryAddress() + pageIndex * PageSize;
        uintptr_t blockAddress = pageAddress + blockIndex * BlockSize;
        reinterpret_cast<PageHeader*>(pageAddress)->freeBlockBit.set(blockIndex);
        return reinterpret_cast<void*>(blockAddress);
    }
    void _Deallocate(size_t pageIndex, size_t blockIndex) {
        uintptr_t pageAddress = GetMemoryAddress() + pageIndex * PageSize;
        reinterpret_cast<PageHeader*>(pageAddress)->freeBlockBit.reset(blockIndex);
    }

    PageHeader* _GetPageHeader(size_t pageIndex) {
        uintptr_t pageAddress = GetMemoryAddress() + pageIndex * PageSize;
        return reinterpret_cast<PageHeader*>(pageAddress);
    }

    size_t _GetPageIndex(void* ptr) {
        uintptr_t pageAddress = reinterpret_cast<uintptr_t>(ptr) & ~(PageSize - 1);
        return (pageAddress - GetMemoryAddress()) / PageSize;
    }
    size_t _GetBlockIndex(void* ptr) {
        return (reinterpret_cast<uintptr_t>(ptr) - GetMemoryAddress()) % PageSize / BlockSize;
    }

    // 最初のビットが立っていないインデックスを返す
    size_t _GetFirstFreeBlockIndex(const PageHeader* pageHeader) {
        for (size_t i = 0; i < pageHeader->freeBlockBit.size(); ++i) {
            if (!pageHeader->freeBlockBit.test(i)) {
                return i;
            }
        }
        return pageHeader->freeBlockBit.size();
    }
};

}  // namespace lib
