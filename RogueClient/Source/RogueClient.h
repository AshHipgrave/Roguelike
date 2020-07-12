#pragma once

#include <SDL.h>

class RogueClient
{
public:
	bool Init(const char* windowTitle, int windowWidth, int windowHeight);
	void LoadResources();

	void Run();

	void Exit();

protected:
	SDL_Window* m_GameWindow = nullptr;
	SDL_Surface* m_WindowSurface = nullptr;

	SDL_Surface* m_TextureSurface = nullptr;
};

