#pragma once

#include "Core/IntrusiveRefCounter.h"

namespace lib {

class FileLoader;
class File;
using FilePtr = IntrusivePtr<File>;

// ファイルを表すクラス
class File : public IntrusiveRefCounter<File> {
public:
    File()                       = default;
    File(const File&)            = delete;
    File& operator=(const File&) = delete;
    File(const FileLoader& loader);

    virtual ~File() = default;

    // データ取得
    void* GetData() const {
        return m_buffer;
    }

    // 指定した型に変換して取得
    template <typename T>
    T* GetData() const {
        return static_cast<T*>(m_buffer);
    }

private:
    void* m_buffer = nullptr;
    size_t m_size = 0;
};
}  // namespace lib
