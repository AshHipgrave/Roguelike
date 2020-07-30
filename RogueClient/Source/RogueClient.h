#pragma once

#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_events.h>
#include <SDL_syswm.h>

#include "GameTimer.h"
#include "RenderText.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

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
	void CalculateFrameStats();

protected:
	GameTimer m_GameTimer;
	
	SDL_Renderer* m_Renderer = nullptr;
	SDL_Window* m_GameWindow = nullptr;

	RenderText* m_DiagnosticText = nullptr;

private:
	bool m_bIsPaused = false;
	bool m_bIsRunning = false;

	bool m_bIsResizing = false;

	bool m_bIsMinimised = false;
	bool m_bIsMaximized = false;
};
