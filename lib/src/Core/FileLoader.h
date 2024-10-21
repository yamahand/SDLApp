#pragma once

#include <bitset>
#include <future>

#include "Core/IntrusivePtr.h"
#include "Core/String.h"
#include "Util/EnumBitset.h"
#include "Util/Function.h"

namespace lib {

class File;
using FilePtr = IntrusivePtr<File>;

class FileLoader {
    enum class Status : uint32_t {
        NotStarted,
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
    using CompleteCallback = Function<void(const void*, const size_t&)>;

public:
    FileLoader()  = default;
    ~FileLoader() = default;

    explicit FileLoader(const String& path);
    FileLoader(const String& path, CompleteCallback completedCallback);
    FileLoader(const String& path, bool async);
    FileLoader(const String& path, CompleteCallback completedCallback, bool async);

    void Load(const String& path, CompleteCallback completedCallback = nullptr, bool async = true);

    void Load();

    const String& GetPath() const {
        return m_path;
    }

    Status GetStatus() const;

    bool IsLoaded() const {
        return GetStatus() == Status::Loaded;
    }

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

    size_t GetSize() const {
        return m_size;
    }

private:
    void _Load();

private:
    String m_path;
    std::atomic<Status> m_status{Status::NotStarted};
    EnumBitset<Flag::Max> m_flags;
    size_t m_size  = 0;
    void* m_buffer = nullptr;
    std::future<void> m_future;
    CompleteCallback m_completedCallback;
};
}  // namespace lib
