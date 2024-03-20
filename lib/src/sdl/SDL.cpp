#include "SDL.h"


#include"imgui/imgui.h"
#include"imgui/backends/imgui_impl_sdl3.h"
#include"imgui/backends/imgui_impl_sdlrenderer3.h"

void SDL::Initalize()
{
	const int WIDTH = 960;
	const int HEIGHT = 720;

	SDL_Init(SDL_INIT_VIDEO);
	m_window = SDL_CreateWindow("Hello SDL", WIDTH, HEIGHT, 0);
	m_renderer = SDL_CreateRenderer(m_window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Platform/Renderer backends
	ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer);
	ImGui_ImplSDLRenderer3_Init(m_renderer);
}

void SDL::GameLoop()
{
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

void SDL::RenderPresent()
{
	SDL_RenderPresent(m_renderer);
}

void SDL::FInalize()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
