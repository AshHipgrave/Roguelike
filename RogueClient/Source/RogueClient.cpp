#include "RogueClient.h"

#include <iostream>

bool RogueClient::Init(const char* windowTitle, int windowWidth, int windowHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return false;

	m_GameWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	if (m_GameWindow == nullptr)
		return false;

	m_WindowSurface = SDL_GetWindowSurface(m_GameWindow);

	return true;
}

void RogueClient::LoadResources()
{
	m_TextureSurface = SDL_LoadBMP("Assets/Images/SpriteSheet_magenta.bmp");
}

void RogueClient::Run()
{
	bool quit = false;

	SDL_Event sdlEvent;

	while (!quit)
	{
		while (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		SDL_BlitSurface(m_TextureSurface, NULL, m_WindowSurface, NULL);

		SDL_UpdateWindowSurface(m_GameWindow);
	}
}

void RogueClient::Exit()
{
	if (m_WindowSurface != nullptr)
	{
		SDL_FreeSurface(m_WindowSurface);
		m_WindowSurface = nullptr;
	}
	
	if (m_GameWindow != nullptr)
	{
		SDL_DestroyWindow(m_GameWindow);
		m_GameWindow = nullptr;
	}

	SDL_Quit();
}
