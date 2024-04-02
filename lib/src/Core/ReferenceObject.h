#pragma once

template <class DerivedT>
class ReferenceObject {
public:
    ReferenceObject()  = default;
    ~ReferenceObject() = default;

private:
    uint32_t m_refCount = 0;

    friend void IncrementReferenceCount(ReferenceObject* obj);
    friend void DecrimentReferenceCount(ReferenceObject* obj)
};

template <class DerivedT>
void IncrementReferenceCount(ReferenceObject<DerivedT>* obj) {
    ++obj->m_refCount;
}

template <class DerivedT>
void DecrimentReferenceCount(ReferenceObject<DerivedT>* obj) {
    --obj->m_refCount;
}
