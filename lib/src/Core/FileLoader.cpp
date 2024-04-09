#include "FileLoader.h"

#include <filesystem>

namespace lib {

FileLoader::FileLoader(const String& path, bool async) {
    Load(path, async);
}

void FileLoader::Load(const String& path, bool async) {
    m_path = path;
    if (async) {
    } else {
        Load();
    }
}

FileLoader::Status FileLoader::GetStatus() const {
    return m_status;
}

void FileLoader::Load() {
    std::filesystem::path path = m_path;
    std::error_code ec;
    if (std::filesystem::exists(path, ec)) {
        const auto fileSize = std::filesystem::file_size(path, ec);
        if (ec) {
            return;
        } else {
        }
    }
}

}  // namespace lib
