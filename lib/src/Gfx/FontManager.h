#pragma once

#include <vector>

#include "stb/stb_truetype.h"
#include "Core/File.h"
#include "Core/Singleton.h"


namespace lib {

class FontManager;

FontManager& GetFontManager() {
    return Singleton<FontManager>::GetInstance();
}

class FontManager {
public:
    FontManager();
    ~FontManager();

public:
    void LoadFont(const char* fontName, const char* fontPath, int fontSize);
    void LoadFont(const char* fontName, const FilePtr& fontFile, int fontSize);

private:
    struct Font {
        const char* name;
        int size;
        stbtt_fontinfo fontInfo;
    };
    std::vector<Font> fontDataList;
};
}  // namespace lib
