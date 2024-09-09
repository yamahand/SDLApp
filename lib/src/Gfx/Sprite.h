#pragma once

#include <cstdint>

#include "Math/Math.h"

namespace lib {
class Sprite {
public:
    Sprite()          = default;
    virtual ~Sprite() = default;

public:
    virtual bool Intialize(const uint8_t* pData, size_t size) = 0;

    virtual void Draw() = 0;

    void Draw(float x, float y) {
        m_position.m128_f32[0] = x;
        m_position.m128_f32[1] = y;
        Draw();
    }

    void SetPosition(const float x, const float y) {
        m_position.m128_f32[0] = x;
        m_position.m128_f32[1] = y;
    }

    void SetPosition(const math::Vector4& position) {
        m_position = position;
    }

    math::Vector4 GetPosition() const {
        return m_position;
    }

    size_t GetWidth() const {
        return m_width;
    }

    size_t GetHeight() const {
        return m_height;
    }

protected:
    math::Vector4 m_position;
    size_t m_width  = 0;
    size_t m_height = 0;
};
}  // namespace lib
