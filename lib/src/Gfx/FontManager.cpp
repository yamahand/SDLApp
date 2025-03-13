#include "Gfx/FontManager.h"

#include <cstdio>
#include <vector>

#include "stb/stb_truetype.h"

namespace lib {
FontManager::FontManager() {
}

FontManager::~FontManager() {
}

void FontManager::LoadFont(const char* fontName, const char* fontPath, int fontSize) {
    // Load font
    stbtt_fontinfo fontInfo;
    unsigned char* fontData = nullptr;
    FILE* fontFile          = fopen(fontPath, "rb");
    if (fontFile) {
        fseek(fontFile, 0, SEEK_END);
        long size = ftell(fontFile);
        fseek(fontFile, 0, SEEK_SET);
        fontData = new unsigned char[size];
        fread(fontData, 1, size, fontFile);
        fclose(fontFile);
    }
    stbtt_InitFont(&fontInfo, fontData, 0);
    // Create font
    Font font;
    font.name     = fontName;
    font.size     = fontSize;
    font.fontInfo = fontInfo;
    fontDataList.push_back(font);
}

void FontManager::LoadFont(const char* fontName, const FilePtr& fontFile, int fontSize) {
    // Load font
    stbtt_fontinfo fontInfo;
    stbtt_InitFont(&fontInfo, fontFile->GetData<unsigned char>(), 0);
    // Create font
    Font font;
    font.name     = fontName;
    font.size     = fontSize;
    font.fontInfo = fontInfo;
    fontDataList.push_back(font);
}
}   // namespace lib
