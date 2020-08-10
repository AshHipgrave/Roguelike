#pragma once

#include <SDL.h>

class RenderImpl
{
public:
	static RenderImpl& Instance() 
	{
		static RenderImpl m_Instance;

		return m_Instance; 
	}

public:
	bool Init(SDL_Window* gameWindow /* TEMP: Move SDL_Window to own instance, similar to renderer */)
	{
		m_Renderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		return m_Renderer != nullptr;
	}

	SDL_Renderer* GetRenderer() const
	{
		return m_Renderer;
	}

private:
	SDL_Renderer* m_Renderer = nullptr;

private:
	RenderImpl();
};

