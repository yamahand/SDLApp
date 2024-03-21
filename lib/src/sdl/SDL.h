#pragma once


struct SDL_Window;
struct SDL_Renderer;

namespace lib {

class SDL {
public:
    SDL() = default;
    ~SDL() = default;

    /// <summary>
    /// SDL������
    /// </summary>
    void Initalize();

    void BeginFrame();
    void EndFrame();
    void GameLoop();

    void RenderPresent();

    /// <summary>
    /// SDL�I��
    /// </summary>
    void FInalize();

    bool IsEnd() const { return m_isEnd; }

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    bool m_isEnd = false;
};

}
