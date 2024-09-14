#include "SDL.h"

#include "SDL3/SDL.h"
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
}  // namespace

namespace lib {

void SDL::Initialize() {
    const int WIDTH  = 1280;
    const int HEIGHT = 720;

    SDL_Init(SDL_INIT_VIDEO);
    m_window   = SDL_CreateWindow("Hello SDL", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    SDL_SetWindowSize(m_window, WIDTH, HEIGHT);
    int32_t w, h;
    SDL_GetWindowSize(m_window, &w, &h);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer3_Init(m_renderer);
}

void SDL::BeginFrame() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL3_ProcessEvent(&event);

        switch (event.type) {
            case SDL_EVENT_QUIT:
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
        int32_t w, h;
        SDL_GetWindowSize(m_window, &w, &h);
        ImGui::Text("%d, %d", w, h);
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
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

SDL& GetSDL() {
    return Singleton<SDL>::GetInstance();
}
}  // namespace lib
