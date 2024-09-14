#include "FileLoader.h"

#include <filesystem>
#include <fstream>
#include <future>

#include "Logger/Logger.h"

namespace lib {

FileLoader::FileLoader(const String& path, bool async) {
    Load(path, async);
}

void FileLoader::Load(const String& path, bool async) {
    m_flags.Set(Flag::Requested, true);
    m_path = path;
    if (async) {
        m_flags.Set(Flag::Async, true);
        m_status = Status::Loading;
        m_future = std::async(std::launch::async, &FileLoader::_Load, this);
    } else {
        _Load();
    }
}

FileLoader::Status FileLoader::GetStatus() const {
    return m_status;
}

void FileLoader::_Load() {
    std::filesystem::path path = m_path;
    std::error_code ec;
    if (std::filesystem::exists(path, ec)) {
        const auto fileSize = std::filesystem::file_size(path, ec);
        if (ec) {
            LOG_ERROR("lib.file", "ファイルサイズの取得に失敗しました: {}", ec.message().c_str());
            m_status = Status::Error;
            return;
        }

        std::ifstream file(path, std::ios::binary);
        if (!file) {
            LOG_ERROR("lib.file", "ファイルのオープンに失敗しました。");
            m_status = Status::Error;
            return;
        }

        m_buffer = malloc(fileSize);
        file.read(static_cast<char*>(m_buffer), fileSize);

        m_status  = Status::Loaded;
        LOG_TRACE("lib.file", "ファイルが正常に読み込まれました。");
    } else {
        LOG_ERROR("lib.file", "ファイルが存在しません: {}", ec.message().c_str());
        m_status = Status::NotFound;
    }
}


}  // namespace lib
