#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Core/Utils.h"
#include "Core/Level.h"
#include "Core/GameTimer.h"

#include "Components/RenderText.h"
#include "Components/Character.h"

#include "Systems/RenderImpl.h"
#include "Systems/GameWindow.h"
#include "Systems/InputManager.h"
#include "Systems/ImGuiImpl.h"

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

private:
	void CalculateFrameStats();

private:
	GameTimer m_GameTimer;

	Level* m_CurrentLevel = nullptr;

	Character* m_PlayerCharacter = nullptr;

	AnimSprite* m_CharactrerSprite = nullptr;

	ImGuiImpl* m_ImGuiContext = nullptr;

	RenderText* m_DiagnosticText = nullptr;

private:
	bool m_bIsPaused = false;
	bool m_bIsRunning = false;

	bool m_bIsMaximised = false;
	bool m_bIsMinimised = false;
};
