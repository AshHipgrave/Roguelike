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

		m_WindowWidth = width;
		m_WindowHeight = height;

		return m_GameWindow != nullptr;
	}

	int GetWindowWidth() const
	{
		return m_WindowWidth;
	}

	int GetWindowHeight() const
	{
		return m_WindowHeight;
	}

	SDL_Window* GetGameWindow() const
	{
		return m_GameWindow;
	}

private:
	SDL_Window* m_GameWindow = nullptr;

	int m_WindowWidth = 0;
	int m_WindowHeight = 0;

private:
	GameWindow() { }
};