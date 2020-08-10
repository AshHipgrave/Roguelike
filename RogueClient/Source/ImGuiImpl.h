#pragma once

#include <SDL.h>

#include <imgui.h>
#include <imgui_sdl.h>

#include "Renderer.h"

class ImGuiImpl
{
public:
	void Init(int windowWidth, int windowHeight);
	void Destroy();

	void HandleEvent(SDL_Event* sdlEvent);

	void Update();
	void Draw();

	bool IsInitialised();

private:
	static const char* GetClipboardText(void*);

	static void SetClipboardText(void*, const char* text);

private:
	bool m_bIsInitialised = false;

	bool m_MouseButtonPressed[3] = { false, false, false };

	SDL_Cursor* m_MouseCursors[ImGuiMouseCursor_COUNT] = {};
};

