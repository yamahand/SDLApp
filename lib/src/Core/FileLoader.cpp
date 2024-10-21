#include "FileLoader.h"

#include <filesystem>
#include <fstream>
#include <future>

#include "Logger/LogLevel.h"
#include "Logger/Logger.h"

namespace lib {
FileLoader::FileLoader(const String& path)
    : m_path(path)
    , m_flags() {
    m_flags.Set(Flag::Async, true);
}
FileLoader::FileLoader(const String& path, CompleteCallback completedCallback)
    : m_path(path)
    , m_flags() {
    m_completedCallback = completedCallback;
    m_flags.Set(Flag::Async, true);
}
FileLoader::FileLoader(const String& path, bool async)
    : m_path(path)
    , m_flags() {
    m_path = path;
    m_flags.Set(Flag::Async, async);
}
FileLoader::FileLoader(const String& path, CompleteCallback completedCallback, bool async)
    : m_path(path)
    , m_flags() {
    m_completedCallback = completedCallback;
    m_flags.Set(Flag::Async, async);
}

void FileLoader::Load(const String& path, CompleteCallback completedCallback, bool async) {
    m_path = path;
    m_flags.Set(Flag::Requested, true);
    m_completedCallback = completedCallback;
}

void FileLoader::Load() {
    if (m_flags.Test(Flag::Async)) {
        m_status.store(Status::Loading);
        m_future = std::async(std::launch::async, &FileLoader::_Load, this);
    } else {
        _Load();
    }
}

FileLoader::Status FileLoader::GetStatus() const {
    return m_status.load();
}

void FileLoader::_Load() {
    std::filesystem::path path = m_path;
    std::error_code ec;
    if (std::filesystem::exists(path, ec)) {
        const auto fileSize = std::filesystem::file_size(path, ec);
        if (ec) {
            LOG_ERROR("lib.file", "ファイルサイズの取得に失敗しました: {}", ec.message().c_str());
            m_status.store(Status::Error);
            return;
        }

        std::ifstream file(path, std::ios::binary);
        if (!file) {
            LOG_ERROR("lib.file", "ファイルのオープンに失敗しました。");
            m_status.store(Status::Error);
            return;
        }

        m_size   = fileSize;
        m_buffer = malloc(fileSize);
        file.read(static_cast<char*>(m_buffer), fileSize);

        m_status.store(Status::Loaded);
        LOG_TRACE("lib.file", "ファイルが正常に読み込まれました。");

        if (m_completedCallback.IsValid()) {
            m_completedCallback(m_buffer, m_size);
        }
    } else {
        LOG_ERROR("lib.file", "ファイルが存在しません: {}", ec.message().c_str());
        m_status.store(Status::NotFound);
    }
}

}  // namespace lib
