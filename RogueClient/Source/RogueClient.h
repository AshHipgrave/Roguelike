#pragma once

#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameTimer.h"
#include "RenderText.h"

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

	RenderText* m_DiagnosticText = nullptr;

private:
	int m_FrameCount = 0;

	bool m_bIsRunning = false;

	const float TARGET_FPS = 60.0f;
	const float TIME_PER_FRAME = (1.0f / TARGET_FPS) * 1000.0f;
};

