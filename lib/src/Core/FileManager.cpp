#include "FileManager.h"

#include "Core/File.h"
#include "Core/FileLoader.h"
#include "Memory/Memory.h"

void lib::FileManager::Initialize() {
    m_files.clear();
    m_loaders.clear();
}

void lib::FileManager::Update() {
    while (!m_loaders.empty()) {
        auto loader = m_loaders.front();
        if (loader->IsLoaded()) {
            m_files[loader->GetPath()] = FilePtr(new File(*loader));
            m_loaders.pop_front();
        } else {
            break;
        }
    }
}

void lib::FileManager::LoadRequest(const String& path, FileLoader::CompleteCallback completeCallback) {
    auto it = m_files.find(path);
    if (it != m_files.end()) {
        return;
    }

    FileLoader* loader = new FileLoader(path, completeCallback);
    loader->Load();
    m_loaders.emplace_back(loader);
}
