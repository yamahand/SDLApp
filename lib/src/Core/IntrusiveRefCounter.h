#pragma once


#include <atomic>   // 追加
#include <cstdint>  // 追加


namespace lib {

template <class DeriveT>
class IntrusiveRefCounter {
public:
    IntrusiveRefCounter() noexcept {};
    IntrusiveRefCounter(IntrusiveRefCounter const& r) noexcept
        : m_refCount(r.m_refCount.load()) {
    }
    IntrusiveRefCounter& operator=(IntrusiveRefCounter const& r) noexcept {
        m_refCount.store(r.m_refCount);
        return this;
    }

    uint32_t UseCount() const noexcept {
        return m_refCount.load();
    }

    virtual ~IntrusiveRefCounter() = default;

private:
    std::atomic<uint32_t> m_refCount = 0;

    friend void IncrementReferenceCount(IntrusiveRefCounter<DeriveT>* obj) noexcept {
        ++obj->m_refCount;
    
    }
    friend void DecrimentReferenceCount(IntrusiveRefCounter<DeriveT>* obj) noexcept {
        --obj->m_refCount;
        if (obj->m_refCount == 0) {
            delete obj;
        }
    }
};

}  // namespace lib
