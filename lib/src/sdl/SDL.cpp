#include "SDL.h"

#include "Core/Assert.h"
#include "Core/Singleton.h"
#include "imgui/backends/imgui_impl_sdl3.h"
#include "imgui/backends/imgui_impl_sdlrenderer3.h"
#include "imgui/imgui.h"

namespace {
char* GetNearbyFilename(const char* file) {
    char* path;

    const auto* base = SDL_GetBasePath();

    if (base) {
        SDL_IOStream* rw;
        size_t len = SDL_strlen(base) + SDL_strlen(file) + 1;

        path = static_cast<char*>(SDL_malloc(len));

        if (!path) {
            return NULL;
        }

        (void)SDL_snprintf(path, len, "%s%s", base, file);

        rw = SDL_IOFromFile(path, "rb");
        if (rw) {
            SDL_CloseIO(rw);
            return path;
        }

        /* Couldn't find the file in the base path */
        SDL_free(path);
    } else {
        const auto* error = SDL_GetError(); /* Clear any error from not having a base path set */
        /* Couldn't get the base path */
        return nullptr;
    }

    return SDL_strdup(file);
}

SDL_Texture* CreateTexture(SDL_Renderer* pRenderer, const uint8_t* pData, const size_t len, int32_t* pWidth, int32_t* pHeight) {
    if (SDL_IOStream* pIOStream = SDL_IOFromConstMem(pData, len)) {
        if (auto pSurface = SDL_LoadBMP_IO(pIOStream, true)) {
            SDL_SetSurfaceColorKey(pSurface, true, *((Uint8*)pSurface->pixels));

            auto pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
            *pWidth       = pSurface->w;
            *pHeight      = pSurface->h;
            SDL_DestroySurface(pSurface);
            return pTexture;
        }
    }

    return nullptr;
}
}  // namespace

namespace lib {

void SDL::Initialize() {
    const int WIDTH  = 1280;
    const int HEIGHT = 720;

    SDL_Init(SDL_INIT_VIDEO);
    m_window   = SDL_CreateWindow("Hello SDL", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    SetWindowSize(WIDTH, HEIGHT);
    SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer3_Init(m_renderer);

    // メインレンダーターゲットの作成
    m_mainRenderTarget = CreateRenderTexture(m_windowWidth, m_windowHeight);
}

void SDL::BeginFrame() {
    SetRenderTarget(m_mainRenderTarget);
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        ImGui_ImplSDL3_ProcessEvent(&sdlEvent);

        SDL_EventType type = static_cast<SDL_EventType>(sdlEvent.type);

        switch (sdlEvent.type) {
            case SDL_EVENT_QUIT:
                m_isEnd = true;
                break;
                // ウインドウのサイズ変更
            case SDL_EVENT_WINDOW_RESIZED:
                SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
                break;
                // ウインドウの閉じるボタンが押された
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                m_isEnd = true;
                break;
        }
    }
    ImGui_ImplSDL3_NewFrame();
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui::NewFrame();

    /* Draw a gray background */
    SDL_SetRenderDrawColor(m_renderer, 0xA0, 0xA0, 0xA0, 0xFF);
    SDL_RenderClear(m_renderer);
}

void SDL::EndFrame() {
    if (ImGui::Begin("window size")) {
        static int32_t windowssize[2] = {0, 0};
        ImGui::InputInt2("Window size", windowssize);
        if (ImGui::Button("SetWindowSize")) {
            SetWindowSize(windowssize[0], windowssize[1]);
        }
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);

    // レンダーターゲットをリセット
    SetRenderTarget(nullptr);
    // メインレンダーターゲットを描画
    SDL_FRect rect{};
    rect.x = 0;
    rect.y = 0;
    rect.w = static_cast<float>(m_windowWidth);
    rect.h = static_cast<float>(m_windowHeight);

    SDL_Renderer* pRenderer = GetSDL().GetRenderer();
    SDL_RenderTexture(pRenderer, m_mainRenderTarget, nullptr, &rect);

    RenderPresent();
}

void SDL::RenderPresent() {
    SDL_RenderPresent(m_renderer);
}

void SDL::FInalize() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void SDL::SetWindowSize(size_t width, size_t height) {
    // ウインドウのサイズを設定する
    auto result = SDL_SetWindowSize(m_window, static_cast<int>(width), static_cast<int>(height));
    PB_WARNING_MSG(result, "sdl", "ウインドウのサイズの設定に失敗しました.");
    SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
}

SDL_Texture* SDL::CreateTexture(SDL_PixelFormat format, SDL_TextureAccess access, int w, int h) const {
    return SDL_CreateTexture(m_renderer, format, access, w, h);
}

SDL_Texture* SDL::CreateRenderTexture(int w, int h, SDL_PixelFormat format) {
    return CreateTexture(format, SDL_TEXTUREACCESS_TARGET, w, h);
}

bool SDL::SetRenderTarget(SDL_Texture* texture) {
    return SDL_SetRenderTarget(m_renderer, texture);
}

SDL& GetSDL() {
    return Singleton<SDL>::GetInstance();
}
}  // namespace lib
