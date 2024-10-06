#pragma once 

namespace lib {

// カスタムアロケータの定義
template <typename T>
struct STLAllocator {
    using value_type = T;

    STLAllocator() = default;

    template <typename U>
    constexpr STLAllocator(const STLAllocator<U>&) noexcept {
    }

    T* allocate(std::size_t n) {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) noexcept {
        ::operator delete(p);
    }
};

template <typename T, typename U>
bool operator==(const STLAllocator<T>&, const STLAllocator<U>&) {
    return true;
}

template <typename T, typename U>
bool operator!=(const STLAllocator<T>&, const STLAllocator<U>&) {
    return false;
}
}
