#include "Sprite.h"

#include "sdl/SDLSprite.h"

namespace lib {

Sprite* Sprite::Create(const uint8_t* pData, size_t size) {
    auto pSprite = new SDLSprite();
    pSprite->Intialize(pData, size);
    return pSprite;
}

}  // namespace lib
