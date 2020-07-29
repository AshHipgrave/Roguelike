#include "RogueClient.h"

#include <iostream>

bool RogueClient::Init(const char* windowTitle, int windowWidth, int windowHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return false;

	m_GameWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	if (m_GameWindow == nullptr)
		return false;

	m_Renderer = SDL_CreateRenderer(m_GameWindow, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(m_Renderer, 100, 149, 237, 255);

	m_GameTimer = new GameTimer();

	return true;
}

void RogueClient::LoadResources()
{

}

void RogueClient::Run()
{
	bool quit = false;

	SDL_Event sdlEvent;

	m_GameTimer->Start();

	while (!quit)
	{
		float avgFPS = m_TotalFrames / (m_GameTimer->GetTicks() / 1000.f);

		if (avgFPS > 2000000) avgFPS = 0;

		while (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		SDL_RenderClear(m_Renderer);

		

		SDL_RenderPresent(m_Renderer);

		m_TotalFrames++;

		int frameTicks = m_GameTimer->GetTicks();

		if (frameTicks < TicksPerFrame)
		{
			SDL_Delay(TicksPerFrame - frameTicks);
		}

		std::cout << "FPS " << avgFPS << " | Frame time " << frameTicks << std::endl;
	}
}

void RogueClient::HandleEvents()
{

}

void RogueClient::Update(float deltaTime)
{

}

void RogueClient::Draw(float deltaTime)
{

}

void RogueClient::Exit()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
	
	if (m_GameWindow != nullptr)
	{
		SDL_DestroyWindow(m_GameWindow);
		m_GameWindow = nullptr;
	}

	SDL_Quit();
}
