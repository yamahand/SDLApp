#pragma once

template <class DeriveT>
class IntrusiveRefCounter {
public:
    IntrusiveRefCounter()                                   = noexcept;
    IntrusiveRefCounter(const IntrusiveRefCounter const& r) = noexcept;
    IntrusiveRefCounter& operator=(IntrusiveRefCounter const& r) noexcept;

    uint32_t UseCount() const noexcept;

protected:
    ~IntrusiveRefCounter() = default;
};
