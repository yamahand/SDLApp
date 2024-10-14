#include "SDLSprite.h"

#include "SDL3/SDL.h"
#include "sdl/SDL.h"

namespace {
SDL_Texture* CreateTexture(SDL_Renderer* pRenderer, const uint8_t* pData, const size_t len, size_t* pWidth, size_t* pHeight) {
    if (SDL_IOStream* pIOStream = SDL_IOFromConstMem(pData, len)) {
        if (auto pSurface = SDL_LoadBMP_IO(pIOStream, SDL_TRUE)) {
            SDL_SetSurfaceColorKey(pSurface, SDL_TRUE, *((Uint8*)pSurface->pixels));

            auto pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
            *pWidth       = pSurface->w;
            *pHeight      = pSurface->h;
            SDL_DestroySurface(pSurface);
            return pTexture;
        }
    }

    return nullptr;
}
}

namespace lib {

SDLSprite::SDLSprite() {
}

SDLSprite::~SDLSprite() {
    if (m_pTexture) {
        SDL_DestroyTexture(m_pTexture);
    }
}
bool SDLSprite::Intialize(const uint8_t* pData, size_t size) {
    SDL_Renderer* pRenderer = GetSDL().GetRenderer();
    m_pTexture           = CreateTexture(pRenderer, pData, size, &m_width, &m_height);
    return m_pTexture == nullptr;
}
void SDLSprite::Draw() {
    SDL_FRect rect{};
    rect.x = m_position.x;
    rect.y = m_position.y;
    rect.w = static_cast<float>(m_width);
    rect.h = static_cast<float>(m_height);

    SDL_Renderer* pRenderer = GetSDL().GetRenderer();
    SDL_RenderTexture(pRenderer, m_pTexture, nullptr, &rect);
}
}  // namespace lib
