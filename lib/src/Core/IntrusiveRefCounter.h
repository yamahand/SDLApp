#pragma once

namespace lib {

template <class DeriveT>
class IntrusiveRefCounter {
public:
    IntrusiveRefCounter() noexcept {};
    IntrusiveRefCounter(IntrusiveRefCounter const& r) noexcept
        : m_refCount(r.m_refCount) {
    }
    IntrusiveRefCounter& operator=(IntrusiveRefCounter const& r) noexcept {
        m_refCount = r.m_refCount;
    }

    uint32_t UseCount() const noexcept {
        return m_refCount;
    }

    virtual ~IntrusiveRefCounter() = default;

private:
    uint32_t m_refCount = 0;

    friend void IncrementReferenceCount(IntrusiveRefCounter<DeriveT>* obj) {
        ++obj->m_refCount;
    
    }
    friend void DecrimentReferenceCount(IntrusiveRefCounter<DeriveT>* obj) {
        --obj->m_refCount;
        if (obj->m_refCount == 0) {
            delete obj;
        }
    }
};

}  // namespace lib
