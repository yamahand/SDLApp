#pragma once

#include "Gfx/Sprite.h"

struct SDL_Texture;
struct SDL_Renderer;

namespace lib {
class SDLSprite : public Sprite {
public:
    SDLSprite();
    ~SDLSprite();

public:
    bool Intialize(const uint8_t* pData, size_t size) override;

    void Draw() override;

private:
    SDL_Texture* m_pTexture   = nullptr;
};
}  // namespace lib
