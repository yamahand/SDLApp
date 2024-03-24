#pragma once

#include <cstdint>

namespace lib {
class Sprite {
public:
    Sprite()          = default;
    virtual ~Sprite() = default;

public:
    virtual bool Intialize(const uint8_t* pData, size_t size) = 0;

    virtual void Draw() = 0;

    void Draw(float x, float y) {
        m_x = x;
        m_y = y;
        Draw();
    }

    void SetPosition(const float x, const float y) {
        m_x = x;
        m_y = y;
    }

    size_t GetWidth() const {
        return m_width;
    }

    size_t GetHeight() const {
        return m_height;
    }

protected:
    float m_x       = 0.0f;
    float m_y       = 0.0f;
    size_t m_width  = 0;
    size_t m_height = 0;
};
}  // namespace lib
