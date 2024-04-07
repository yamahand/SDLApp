#pragma once

#include "Core/IntrusiveRefCounter.h"

namespace lib {

template <class T>
class IntrusivePtr {
public:
    IntrusivePtr() = default;
    IntrusivePtr(T* p, bool isAddRef = true)
        : m_ptr(p) {
        if (m_ptr && isAddRef) {
            IncrementReferenceCount(m_ptr);
        }
    }
    IntrusivePtr(IntrusivePtr const& r)
        : m_ptr(r.Get()) {
        if (m_ptr) {
            IncrementReferenceCount(m_ptr);
        }
    }

    template <class Y>
    IntrusivePtr(IntrusivePtr<Y> const& r)
        : m_ptr(r.Get()) {
        if (m_ptr) {
            IncrementReferenceCount(m_ptr);
        }
    }

    ~IntrusivePtr() {
        if (m_ptr) {
            DecrimentReferenceCount(m_ptr);
        }
    }

    void Reset();
    void Reset(T* p);
    void Reset(T* p, bool isAddRef);
    void Swap(IntrusivePtr& p);

    IntrusivePtr& operator=(IntrusivePtr const& r);
    template <class Y>
    IntrusivePtr& operator=(IntrusivePtr<Y> const& r);
    IntrusivePtr& operator=(T* p);

    T& operator*() const;
    T* operator->() const;
    T* Get() const;
    T* Detach();

    operator bool() const {
        m_ptr != nullptr;
    }
    bool operator!() const {
        m_ptr == nullptr;
    }

private:
    T* m_ptr = nullptr;
};


template <class T>
void IntrusivePtr<T>::Reset() {
    if (m_ptr) {
        DecrimentReferenceCount(m_ptr);
    }
    m_ptr = nullptr;
}

template <class T>
void IntrusivePtr<T>::Reset(T* p) {
    Reset();
    m_ptr = p;
    if (m_ptr) {
        IncrementReferenceCount(m_ptr);
    }
}

template <class T>
void IntrusivePtr<T>::Reset(T* p, bool isAddRef) {
    Reset();
    m_ptr = p;
    if (isAddRef && m_ptr) {
        IncrementReferenceCount(m_ptr);
    }
}

template <class T>
void IntrusivePtr<T>::Swap(IntrusivePtr& p) {
    std::swap(m_ptr, p.m_ptr);
}

template <class T>
IntrusivePtr<T>& IntrusivePtr<T>::operator=(IntrusivePtr<T> const& r) {
    IntrusivePtr(r).swap(*this);
    return *this;
}


template <class T>
IntrusivePtr<T>& IntrusivePtr<T>::operator=(T* p) {
    IntrusivePtr(p).swap(*this);
    return *this;
}

template <class T>
T& IntrusivePtr<T>::operator*() const {
    return *m_ptr;
}

template <class T>
T* IntrusivePtr<T>::operator->() const {
    return m_ptr;
}

template <class T>
T* IntrusivePtr<T>::Get() const {
    return m_ptr;
}

template <class T>
T* IntrusivePtr<T>::Detach() {
    auto* p = m_ptr;
    m_ptr   = nullptr;
    return p;
}

// #endif  // IntrusivePtr_IMPL

// #define IntrusivePtr_IMPL
// #include "IntrusivePtr.inl"
// #undef IntrusivePtr_IMPL

}  // namespace lib
