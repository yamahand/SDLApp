#pragma once

#include <bitset>

#include "Core/IntrusivePtr.h"
#include "Core/String.h"
#include "Util/EnumBitset.h"

namespace lib {

class File;
using FilePtr = IntrusivePtr<File>;

class FileLoader {
    enum class Status : uint32_t {
        None,
        Loading,
        Loaded,
        Error,
        NotFound,

        Max,
    };

    enum class Flag : uint32_t {
        Requested,
        Async,

        Max,
    };

public:
    FileLoader()  = default;
    ~FileLoader() = default;

    FileLoader(const String& path, bool async = true);

    void Load(const String& path, bool async = true);

    Status GetStatus() const;

    void* GetBuffer() const {
		return m_buffer;
	}

	template <typename T>
	T* GetBuffer() const {
		return static_cast<T*>(m_buffer);
	}

	template <typename T>
	T* GetBuffer(size_t offset) const {
		return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(m_buffer) + offset);
	}

private:
    void _Load();

private:
    String m_path;
    Status m_status = Status::None;
    EnumBitset<Flag::Max> m_flags;
    void* m_buffer = nullptr;
    std::future<void> m_future;
};
}  // namespace lib
