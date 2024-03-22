#include "SDL.h"

#include "SDL3/SDL.h"
#include "imgui/backends/imgui_impl_sdl3.h"
#include "imgui/backends/imgui_impl_sdlrenderer3.h"
#include "imgui/imgui.h"

namespace {
char* GetNearbyFilename(const char* file) {
    char* base;
    char* path;

    base = SDL_GetBasePath();

    if (base) {
        SDL_IOStream* rw;
        size_t len = SDL_strlen(base) + SDL_strlen(file) + 1;

        path = static_cast<char*>(SDL_malloc(len));

        if (!path) {
            SDL_free(base);
            return NULL;
        }

        (void)SDL_snprintf(path, len, "%s%s", base, file);
        SDL_free(base);

        rw = SDL_IOFromFile(path, "rb");
        if (rw) {
            SDL_CloseIO(rw);
            return path;
        }

        /* Couldn't find the file in the base path */
        SDL_free(path);
    }

    return SDL_strdup(file);
}
}  // namespace

namespace lib {

void SDL::Initalize() {
    const int WIDTH  = 960;
    const int HEIGHT = 720;

    SDL_Init(SDL_INIT_VIDEO);
    m_window   = SDL_CreateWindow("Hello SDL", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    m_renderer = SDL_CreateRenderer(m_window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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
}

void SDL::EndFrame() {
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(m_renderer);
}

void SDL::GameLoop() {
    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
        }
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        SDL_Delay(16);

        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
        RenderPresent();
    }
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
}  // namespace lib
