#pragma once

#include <bitset>
#include <concepts>
#include <initializer_list>
#include <type_traits>

namespace lib {

template <auto EnumMax>
    requires std::is_enum_v<decltype(EnumMax)>
class EnumBitset {
    using Enum = decltype(EnumMax);
    using Base = std::bitset<static_cast<size_t>(EnumMax)>;
    using _Ty = std::conditional_t<static_cast<size_t>(EnumMax) <= sizeof(unsigned long) * CHAR_BIT, unsigned long, unsigned long long>;

public:
    EnumBitset() = default;

    constexpr EnumBitset(Enum e) noexcept
        : m_bitset(ToSizeT(e)) {
    }

    constexpr EnumBitset(_Ty val) noexcept
        : m_bitset(val) {
    }

    constexpr EnumBitset(std::initializer_list<Enum> posList) noexcept
        : m_bitset(ToTy(posList)) {
    }

    EnumBitset& Set(Enum e, bool value = true) noexcept {
        m_bitset.set(ToSizeT(e), value);
        return *this;
    }

    EnumBitset& Reset(Enum e) noexcept {
        m_bitset.reset(ToSizeT(e));
        return *this;
    }

    EnumBitset& Flip(Enum e) noexcept {
        m_bitset.flip(ToSizeT(e));
        return *this;
    }

    bool Test(Enum e) const noexcept {
        return m_bitset.test(ToSizeT(e));
    }

    bool All() const noexcept {
        return m_bitset.all();
    }

    bool Any() const noexcept {
        return m_bitset.any();
    }

    bool None() const noexcept {
        return m_bitset.none();
    }

    size_t Count() const noexcept {
        return m_bitset.count();
    }

    size_t Size() const noexcept {
        return m_bitset.size();
    }

    std::string ToString() const noexcept {
        return m_bitset.to_string();
    }

    unsigned long ToULong() const noexcept {
        return m_bitset.to_ulong();
    }

    unsigned long long ToULLong() const noexcept {
        return m_bitset.to_ullong();
    }

    _NODISCARD bool operator[](Enum e) const noexcept {
        return m_bitset.operator[](ToSizeT(e));
    }

    _NODISCARD Base::reference operator[](Enum e) noexcept {
        return m_bitset[ToSizeT(e)];
    }

    _NODISCARD bool operator==(const EnumBitset& rhs) const noexcept {
        return m_bitset == rhs.m_bitset;
    }

private:
    static constexpr size_t ToSizeT(Enum e) noexcept {
        return static_cast<size_t>(e);
    }

    static constexpr _Ty ToTy(std::initializer_list<Enum> posList) noexcept {
        _Ty val = 0;
        for (auto pos : posList) {
            val |= 1 << ToSizeT(pos);
        }
        return val;
    }

    private:
        std::bitset<static_cast<size_t>(EnumMax)> m_bitset;
};

}  // namespace lib
