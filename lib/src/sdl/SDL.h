#pragma once

#include "SDL3/SDL.h"

class SDL{
public:
    SDL() = default;
    ~SDL() = default;

    /// <summary>
    /// SDL������
    /// </summary>
    void Initalize();

    void GameLoop();

    void RenderPresent();

    /// <summary>
    /// SDL�I��
    /// </summary>
    void FInalize();
    
private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
};
