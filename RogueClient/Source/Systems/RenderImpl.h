#pragma once

#include <SDL.h>

#include "GameWindow.h"

class RenderImpl
{
public:
	static RenderImpl& Instance();

public:
	bool Init();

	int GetRenderWidth() const;
	int GetRenderHeight() const;

	SDL_Renderer* GetRenderer() const;

private:
	SDL_Renderer* m_Renderer = nullptr;

	int m_RenderResolutionWidth = 0;
	int m_RenderResolutionHeight = 0;

private:
	RenderImpl() { }
};