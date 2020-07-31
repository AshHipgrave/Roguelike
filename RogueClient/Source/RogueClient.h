#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Utils.h"
#include "GameTimer.h"
#include "RenderText.h"
#include "ImGuiImpl.h"
#include "Sprite.h"

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

	Sprite* m_CharactrerSprite = nullptr;

	ImGuiImpl* m_ImGuiContext = nullptr;
	
	SDL_Renderer* m_Renderer = nullptr;
	SDL_Window* m_GameWindow = nullptr;

	RenderText* m_DiagnosticText = nullptr;

private:
	bool m_bIsPaused = false;
	bool m_bIsRunning = false;

	bool m_bIsMaximised = false;
	bool m_bIsMinimised = false;
};
