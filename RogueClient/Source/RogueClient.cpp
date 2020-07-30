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

	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);

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

	m_GameTimer.Reset();

	while (m_bIsRunning)
	{
		HandleEvents();

		m_GameTimer.Tick();

		float deltaTime = m_GameTimer.GetDeltaTime();
		m_TotalTime += deltaTime;

		if (!m_bIsPaused)
		{
			Update(deltaTime);
			Draw(deltaTime);

			m_FrameCount++;
		}
	}

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
		else if (sdlEvent.type == SDL_SYSWMEVENT)
		{
			switch (sdlEvent.syswm.msg->msg.win.msg)
			{
				case WM_ENTERSIZEMOVE:
					m_bIsPaused = true;
					m_bIsResizing = true;

					m_GameTimer.Stop();

					break;

				case WM_EXITSIZEMOVE:
					m_bIsPaused = false;
					m_bIsResizing = false;

					m_GameTimer.Start();

					break;

			}
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

	static int frameCount = 0;
	static float timeElapsed = 0.0f;

	static float prevFPS = 0.0f;
	static float prevMSPerFrame = 0.0f;

	frameCount++;

	if (m_GameTimer.GetTotalTime() - timeElapsed >= 1.0f)
	{
		float fps = (float)frameCount; //(float)frameCount / m_Timer.GetTotalTime();
		float msPerFrame = 1000.0f / fps;

		std::string debugText("FPS: " + std::to_string(fps) + " ( " + std::to_string(msPerFrame) + "ms ) ");

		m_DiagnosticText->Draw(debugText.c_str(), 0, 0, m_Renderer);

		prevFPS = fps;
		prevMSPerFrame = msPerFrame;

		frameCount = 0;
		timeElapsed += 1.0f;
	}
	else
	{
		std::string debugText("FPS: " + std::to_string(prevFPS) + " ( " + std::to_string(prevMSPerFrame) + "ms ) "); 
		m_DiagnosticText->Draw(debugText.c_str(), 0, 0, m_Renderer);
	}

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
