#pragma once

#include "Core/IntrusivePtr.h"
#include "Core/File.h"
#include "Core/FileLoader.h"

// ファイルマネージャー
namespace lib {
class FileManager {
public:
    FileManager() = default;

    ~FileManager() = default;

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

private:
};
}  // namespace lib
