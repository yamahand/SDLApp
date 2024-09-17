#include <functional>
#include <iostream>
#include <vector>

#include "Util/Function.h"

namespace lib {

template <typename T>
class ObservableVariable {
public:
    using CallbackType = Function<void(const T&, const T&)>;

    ObservableVariable(T value)
        : m_value(value) {
    }
    ObservableVariable(T value, CallbackType callback)
        : m_value(value), m_callback(callback) {
    }

    void SetValue(T newValue) {
        if (m_value != newValue) {
            T oldValue = m_value;
            m_value    = newValue;
            NotifyCallbacks(oldValue, newValue);
        }
    }

    T GetValue() const {
        return m_value;
    }

    operator T() const {
        return m_value;
    }
    ObservableVariable& operator = (const T& newValue) {
        SetValue(newValue);
        return *this;
    }

    void RegisterCallback(CallbackType callback) {
        m_callback = callback;
    }

    void UnregisterCallback() {
		m_callback = nullptr;
	}

private:
    void NotifyCallbacks(const T& oldValue, const T& newValue) {
        if (m_callback.IsValid()) {
            m_callback(oldValue, newValue);
        }
    }

    T m_value = {};
    CallbackType m_callback;
};

}  // namespace lib
