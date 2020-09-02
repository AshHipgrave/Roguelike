#pragma once

#include <SDL.h>

class GameWindow
{
public:
	static GameWindow& Instance()
	{
		static GameWindow m_Instance;

		return m_Instance;
	}

public:
	bool Init(const char* windowTitle, int width, int height)
	{
		m_GameWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		SDL_SetWindowResizable(m_GameWindow, SDL_TRUE);

		return m_GameWindow != nullptr;
	}

	SDL_Window* GetGameWindow() const
	{
		return m_GameWindow;
	}

private:
	SDL_Window* m_GameWindow = nullptr;

private:
	GameWindow() { }
};