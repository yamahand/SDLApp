#pragma once

#include <memory>
#include <utility>

namespace lib {

template <typename T>
struct FunctionAllocator {
    using value_type    = T;
    FunctionAllocator() = default;

    template <typename U>
    constexpr FunctionAllocator(const FunctionAllocator<U>&) noexcept {};

    T* allocate(std::size_t n) {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) noexcept {
        ::operator delete(p);
    }
};

template <>
struct FunctionAllocator<void> {
    using value_type    = void;
    FunctionAllocator() = default;

    template <typename U>
    constexpr FunctionAllocator(const FunctionAllocator<U>&) noexcept {};

    void* allocate(std::size_t n) {
        return ::operator new(n);
    }

    void deallocate(void* p, std::size_t n) noexcept {
        ::operator delete(p);
    }
};

template <typename T, typename U>
bool operator==(const FunctionAllocator<T>&, const FunctionAllocator<U>&) {
    return true;
}

template <typename T, typename U>
bool operator!=(const FunctionAllocator<T>&, const FunctionAllocator<U>&) {
    return false;
}

template <typename Signature, typename Allocator = FunctionAllocator<void>>
class Function;

template <typename R, typename... Args, typename Allocator>
class Function<R(Args...), Allocator> {
public:
    using allocaor_type = Allocator;

    Function() noexcept
        : m_callable(nullptr) {
    }

    template <typename F>
    Function(F&& f, const allocaor_type& alloc = allocaor_type())
        : m_callable(nullptr), allocator(alloc) {
        void* memory = allocator.allocate(sizeof(CallableImpl<F>));
        // プレースメントnewを使用して、割り当てたメモリにCalllableImplオブジェクトを構築
        m_callable.reset(new (memory) CallableImpl<F>(std::forward<F>(f), alloc));
    }

    // コピーコンストラクタ
    Function(const Function& other)
        : allocator(other.allocator) {
        if (other.m_callable) {
            m_callable = other.m_callable->Clone();
        }
    }

    // ムーブコンストラクタ
    Function(Function&& other) noexcept
        : m_callable(std::move(other.m_callable)), allocator(std::move(other.allocator)) {
        other.m_callable = nullptr;
    }

    // コピー代入演算子
    Function& operator=(const Function& other) {
        if (this != &other) {
            allocator = other.allocator;
            if (other.m_callable) {
                m_callable = other.m_callable->Clone();
            } else {
                m_callable.reset();
            }
        }
        return *this;
    }

    // ムーブ代入演算子
    Function& operator=(Function&& other) noexcept {
        if (this != &other) {
            m_callable       = std::move(other.m_callable);
            allocator        = std::move(other.allocator);
            other.m_callable = nullptr;
        }
        return *this;
    }

    R operator()(Args... args) {
        if (m_callable) {
            return m_callable->Invoke(std::forward<Args>(args)...);
        }
        if constexpr (!std::is_void_v<R>) {
            return R();
        }
    }

    _NODISCARD bool IsValid() const noexcept {
        return m_callable != nullptr;
    }

private:
    struct CallableBase {
        virtual ~CallableBase()                             = default;
        virtual R Invoke(Args... args)                      = 0;
        virtual std::unique_ptr<CallableBase> Clone() const = 0;
    };

    template <typename F>
    struct CallableImpl : CallableBase {
        F func;
        allocaor_type allocator;

        CallableImpl(F&& f, const allocaor_type& alloc)
            : func(std::forward<F>(f)), allocator(alloc) {
        }

        CallableImpl(const CallableImpl& other)
            : func(other.func), allocator(other.allocator) {
        }

        R Invoke(Args... args) override {
            return func(std::forward<Args>(args)...);
        }

        std::unique_ptr<CallableBase> Clone() const override {
            return std::make_unique<CallableImpl>(*this);
        }
    };

private:
    std::unique_ptr<CallableBase> m_callable = nullptr;
    allocaor_type allocator;
};


}  // namespace lib
