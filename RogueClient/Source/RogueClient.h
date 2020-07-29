#pragma once

#include <SDL.h>

#include "GameTimer.h"

class RogueClient
{
public:
	bool Init(const char* windowTitle, int windowWidth, int windowHeight);
	void LoadResources();

	void Run();

	void HandleEvents();
	void Update(float deltaTime);
	void Draw(float deltaTime);

	void Exit();

protected:
	GameTimer* m_GameTimer = nullptr;
	SDL_Renderer* m_Renderer = nullptr;

	SDL_Window* m_GameWindow = nullptr;

private:
	int m_TotalFrames = 0;

	const int TargetFPS = 60;
	const int TicksPerFrame = 1000 / TargetFPS;
};

