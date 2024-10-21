#pragma once

#include "Core/IntrusivePtr.h"
#include "Core/File.h"
#include "Core/FileLoader.h"
#include "Core/Singleton.h"
#include "Memory/STLAllocator.h"

#include <queue>

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

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 非同期のファイル読み込みリクエスト
    void LoadRequest(const String& path, FileLoader::CompleteCallback completeCallback = nullptr);

    /// <summary>
    /// 読み込んだファイルの取得
    /// </summary>
    const FilePtr GetFile(const String& path) const {
		auto it = m_files.find(path);
		if (it != m_files.end()) {
			return it->second;
		}
		return nullptr;
	}

private:
    std::unordered_map<String, FilePtr> m_files;
    std::deque<FileLoader*, STLAllocator<FileLoader*>> m_loaders;
    std::mutex m_mutex;
};

static FileManager& GetFileManager() {
    return Singleton<FileManager>::GetInstance();
}

}  // namespace lib
