#include "RogueClient.h"

bool RogueClient::Init(const char* windowTitle, int windowWidth, int windowHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return false;

	if (TTF_Init() != 0)
		return false;

	m_GameWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	if (m_GameWindow == nullptr)
		return false;

	m_Renderer = SDL_CreateRenderer(m_GameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(m_Renderer, 100, 149, 237, 255);

	m_GameTimer = new GameTimer();

	LoadResources();

	return true;
}

void RogueClient::LoadResources()
{
	m_DiagnosticText = new RenderText();
}

void RogueClient::Run()
{
	m_bIsRunning = true;

	m_GameTimer->Start();

	while (m_bIsRunning)
	{
		m_GameTimer->Tick();
		float deltaTime = m_GameTimer->GetDeltaTime();

		HandleEvents();

		Update(deltaTime);
		Draw(deltaTime);

		m_FrameCount++;
	}

	m_GameTimer->Stop();
	Exit();
}

void RogueClient::HandleEvents()
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		if (sdlEvent.type == SDL_QUIT)
		{
			m_bIsRunning = false;
		}
	}
}

void RogueClient::Update(float deltaTime)
{
	// TODO: Update logic here.
}

void RogueClient::Draw(float deltaTime)
{
	SDL_RenderClear(m_Renderer);

	float fps = m_FrameCount / (m_GameTimer->GetTotalTime() * m_GameTimer->GetFrequency());

	std::string debugText("FPS: " + std::to_string(fps));

	m_DiagnosticText->Draw(debugText.c_str(), 0, 0, m_Renderer);

	SDL_RenderPresent(m_Renderer);
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
