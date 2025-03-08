#pragma once

#include "Gfx/Sprite.h"

struct SDL_Texture;
struct SDL_Renderer;

namespace lib {
/// <summary>
/// スプライトのSDL実装
/// </summary>
class SDLSprite : public Sprite {
public:
    SDLSprite();
    ~SDLSprite();

public:
    /// <summary>
    ///  初期化
    /// </summary>
    /// <param name="pData">データのアドレス</param>
    /// <param name="size">データサイズ</param>
    /// <returns></returns>
    bool Intialize(const uint8_t* pData, size_t size) override;

    void Finalize() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;

private:
    SDL_Texture* m_pTexture   = nullptr;
};
}  // namespace lib
