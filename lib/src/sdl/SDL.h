#pragma once

struct SDL_Window;
struct SDL_Renderer;

namespace lib {

class SDL;

SDL& GetSDL();

class SDL {
public:
    SDL()  = default;
    ~SDL() = default;

    /// <summary>
    /// SDL初期化
    /// </summary>
    void Initialize();

    void BeginFrame();
    void EndFrame();

    void RenderPresent();

    /// <summary>
    /// SDL終了
    /// </summary>
    void FInalize();

    bool IsEnd() const {
        return m_isEnd;
    }

    SDL_Window* GetWindow() const {
        return m_window;
    }

    SDL_Renderer* GetRenderer() const {
        return m_renderer;
    }

private:
    SDL_Window* m_window     = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    bool m_isEnd             = false;
};

}  // namespace lib
