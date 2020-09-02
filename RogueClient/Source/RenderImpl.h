#pragma once

#include <SDL.h>

#include "GameWindow.h"

class RenderImpl
{
public:
	static RenderImpl& Instance() 
	{
		static RenderImpl m_Instance;

		return m_Instance; 
	}

public:
	bool Init()
	{
		m_Renderer = SDL_CreateRenderer(GameWindow::Instance().GetGameWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		return m_Renderer != nullptr;
	}

	SDL_Renderer* GetRenderer() const
	{
		return m_Renderer;
	}

private:
	SDL_Renderer* m_Renderer = nullptr;

private:
	RenderImpl() { }
};