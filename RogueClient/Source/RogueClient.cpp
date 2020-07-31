#include "RogueClient.h"

bool RogueClient::Init(const char* windowTitle, int windowWidth, int windowHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return false;

	if (TTF_Init() != 0)
		return false;

	if (!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
		return false;

	m_GameWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	SDL_SetWindowResizable(m_GameWindow, SDL_TRUE);

	if (m_GameWindow == nullptr)
		return false;

	m_Renderer = SDL_CreateRenderer(m_GameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(m_Renderer, 100, 149, 237, 255);

	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);

	//m_ImGuiContext = new ImGuiImpl();
	//m_ImGuiContext->Init(m_Renderer, windowWidth, windowHeight);

	LoadResources();

	return true;
}

void RogueClient::LoadResources()
{
	m_DiagnosticText = new RenderText(m_Renderer);
	m_CharactrerSprite = new Sprite("Assets\\Images\\Character.png", 60, 88, 960, 540, m_Renderer);
}

void RogueClient::Run()
{
	m_bIsRunning = true;

	m_GameTimer.Reset();

	while (m_bIsRunning)
	{
		HandleEvents();

		m_GameTimer.Tick();

		if (!m_bIsPaused)
		{
			Update(&m_GameTimer);

			Clear();
			Draw();
			Present();

			CalculateFrameStats();
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
		else if (sdlEvent.type == SDL_WINDOWEVENT)
		{
			switch (sdlEvent.window.event)
			{
				case SDL_WINDOWEVENT_RESTORED:
					if (m_bIsMaximised)
					{
						m_bIsMaximised = false;
						m_bIsMinimised = false;
					}
					else
					{
						m_bIsMinimised = false;
						m_bIsPaused = false;

						m_GameTimer.Start();
					}
					break;

				case SDL_WINDOWEVENT_MAXIMIZED:
					if (!m_bIsPaused)
					{
						m_bIsMaximised = true;
					}
					else
					{
						m_bIsPaused = false;
						m_bIsMinimised = false;

						m_GameTimer.Start();
					}
					break;

				case SDL_WINDOWEVENT_MINIMIZED:
					m_bIsPaused = true;

					m_bIsMinimised = true;
					m_bIsMaximised = false;

					m_GameTimer.Stop();
					
					break;

				case SDL_WINDOWEVENT_RESIZED:
					int x, y;
					SDL_GetWindowSize(m_GameWindow, &x, &y);

					x /= 2;
					y /= 2;

					m_CharactrerSprite->Move(x, y);
					break;
			}
		}

		//m_ImGuiContext->HandleEvent(&sdlEvent);
	}
}

void RogueClient::Update(GameTimer* timer)
{
	// TODO: Additional update logic here.

	//m_ImGuiContext->Update();
}

void RogueClient::Clear()
{
	SDL_RenderClear(m_Renderer);
}

void RogueClient::Draw()
{
	//m_ImGuiContext->Draw();

	m_DiagnosticText->Draw();
	m_CharactrerSprite->Draw();

	//TODO: Additional draw logic here.	
}

void RogueClient::Present()
{
	SDL_RenderPresent(m_Renderer);
}

void RogueClient::Exit()
{
	if (m_ImGuiContext != nullptr)
	{
		m_ImGuiContext->Destroy();
		m_ImGuiContext = nullptr;
	}

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

	TTF_Quit();
	SDL_Quit();
}

void RogueClient::CalculateFrameStats()
{
	static int frameCount = 0;
	static float timeElapsed = 0.0f;

	frameCount++;

	if (m_GameTimer.GetTotalTime() - timeElapsed >= 1.0f)
	{
		float fps = (float)frameCount;
		float msPerFrame = 1000.0f / fps;

		std::string debugText("FPS: " + Utils::float_to_str(fps, 0) + " (" + Utils::float_to_str(msPerFrame) + "ms)");

		m_DiagnosticText->SetText(debugText.c_str());

		frameCount = 0;
		timeElapsed += 1.0f;
	}
}
