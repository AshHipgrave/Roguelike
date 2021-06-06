#include "Systems/GameWindow.h"

GameWindow& GameWindow::Instance()
{
	static GameWindow m_Instance;

	return m_Instance;
}

bool GameWindow::Init(const char* windowTitle, int width, int height, bool resizable)
{
	m_GameWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	
	if (resizable)
	{
		SDL_SetWindowResizable(m_GameWindow, SDL_TRUE);
	}

	m_WindowWidth = width;
	m_WindowHeight = height;

	return m_GameWindow != nullptr;
}

int GameWindow::GetWindowWidth() const
{
	return m_WindowWidth;
}

int GameWindow::GetWindowHeight() const
{
	return m_WindowHeight;
}

SDL_Window* GameWindow::GetGameWindow() const
{
	return m_GameWindow;
}