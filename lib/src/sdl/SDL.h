#pragma once

#include "SDL3/SDL.h"

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

    /// <summary>
    /// フレームの開始処理
    /// </summary>
    void BeginFrame();

    /// <summary>
    /// フレームの終了処理
    /// </summary>
    void EndFrame();

    /// <summary>
    /// レンダリング結果を画面に表示
    /// </summary>
    void RenderPresent();

    /// <summary>
    /// SDL終了
    /// </summary>
    void FInalize();

    /// <summary>
    /// アプリケーションの終了状態を確認
    /// </summary>
    /// <returns>終了状態</returns>
    bool IsEnd() const {
        return m_isEnd;
    }

    /// <summary>
    /// ウインドウのサイズ設定
    /// </summary>
    /// <param name="width">ウインドウの幅</param>
    /// <param name="height">ウインドウの高さ</param>
    void SetWindowSize(size_t width, size_t height);

    /// <summary>
    /// SDLウインドウの取得
    /// </summary>
    /// <returns>SDLウインドウ</returns>
    SDL_Window* GetWindow() const {
        return m_window;
    }

    /// <summary>
    /// SDLレンダラーの取得
    /// </summary>
    /// <returns>SDLレンダラー</returns>
    SDL_Renderer* GetRenderer() const {
        return m_renderer;
    }

    /// <summary>
    /// テクスチャの作成
    /// </summary>
    /// <param name="format">ピクセルフォーマット</param>
    /// <param name="access">テクスチャアクセス</param>
    /// <param name="w">幅</param>
    /// <param name="h">高さ</param>
    /// <returns>SDLテクスチャ</returns>
    SDL_Texture* CreateTexture(SDL_PixelFormat format, SDL_TextureAccess access, int w, int h) const;

    /// <summary>
    /// レンダーターゲットの作成
    /// </summary>
    /// <param name="w">幅</param>
    /// <param name="h">高さ</param>
    /// <param name="format">ピクセルフォーマット</param>
    /// <returns>レンダーテクスチャ</returns>
    SDL_Texture* CreateRenderTexture(int w, int h, SDL_PixelFormat format = SDL_PIXELFORMAT_ARGB8888);

    bool SetRenderTarget(SDL_Texture* texture);

private:
    SDL_Window* m_window            = nullptr;
    SDL_Renderer* m_renderer        = nullptr;
    int32_t  m_windowWidth          = 1280;
    int32_t  m_windowHeight         = 720;
    bool m_isEnd                    = false;
    SDL_Texture* m_mainRenderTarget = nullptr;
};

}  // namespace lib
