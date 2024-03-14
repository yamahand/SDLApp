#include "SDL.h"

void SDL::Initalize()
{
	const int WIDTH = 640;
	const int HEIGHT = 480;

	SDL_Init(SDL_INIT_VIDEO);
	m_window = SDL_CreateWindow("Hello SDL", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
	m_renderer = SDL_CreateRenderer(m_window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void SDL::GameLoop()
{
	while (true) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {

		}
		SDL_Delay(16);
		RenderPresent();
	}
}

void SDL::RenderPresent()
{
	SDL_RenderPresent(m_renderer);
}

void SDL::FInalize()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
