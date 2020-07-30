#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "Utils.h"
#include "GameTimer.h"
#include "RenderText.h"

class RogueClient
{
public:
	bool Init(const char* windowTitle, int windowWidth, int windowHeight);
	void LoadResources();

	void Run();

	void HandleEvents();
	void Update(GameTimer* timer);

	void Clear();
	void Draw();
	void Present();

	void Exit();

protected:
	void CalculateFrameStats();

protected:
	GameTimer m_GameTimer;
	
	SDL_Renderer* m_Renderer = nullptr;
	SDL_Window* m_GameWindow = nullptr;

	RenderText* m_DiagnosticText = nullptr;

private:
	bool m_bIsPaused = false;
	bool m_bIsRunning = false;
};
