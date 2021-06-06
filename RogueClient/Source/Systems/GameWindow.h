#pragma once

#include <SDL.h>

class GameWindow
{
public:
	static GameWindow& Instance();

public:
	bool Init(const char* windowTitle, int width, int height, bool resizable);

	int GetWindowWidth() const;

	int GetWindowHeight() const;

	SDL_Window* GetGameWindow() const;

private:
	SDL_Window* m_GameWindow = nullptr;

	int m_WindowWidth = 0;
	int m_WindowHeight = 0;

private:
	GameWindow() { }
};