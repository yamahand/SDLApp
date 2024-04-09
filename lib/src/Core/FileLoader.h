#pragma once

#include "Core/IntrusivePtr.h"
#include "Core/String.h"

namespace lib {

class File;
using FilePtr = IntrusivePtr<File>;

class FileLoader {
    enum class Status : uint32_t {
        None,
        Loading,
        Succeeded,
        Failed,

        Max,
    };

public:
    FileLoader()  = default;
    ~FileLoader() = default;

    FileLoader(const String& path, bool async = true);

    void Load(const String& path, bool async = true);

    Status GetStatus() const;

private:
    void Load();

private:
    String m_path;
    Status m_status = Status::None;
};
}  // namespace lib
