#include "RogueClient.h"

bool RogueClient::Init(const char* windowTitle, int windowWidth, int windowHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return false;

	if (TTF_Init() != 0)
		return false;

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		return false;

	if (!GameWindow::Instance().Init(windowTitle, windowWidth, windowHeight))
		return false;

	if (!RenderImpl::Instance().Init())
		return false;

	SDL_SetRenderDrawColor(RenderImpl::Instance().GetRenderer(), 100, 149, 237, 255);

	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);

	//m_ImGuiContext = new ImGuiImpl();
	//m_ImGuiContext->Init(m_Renderer, windowWidth, windowHeight);

	LoadResources();

	return true;
}

void RogueClient::LoadResources()
{
	m_DiagnosticText = new RenderText();

	m_PlayerCharacter = new Character(960, 540);
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
					SDL_GetWindowSize(GameWindow::Instance().GetGameWindow(), &x, &y);

					x /= 2;
					y /= 2;

					m_CharactrerSprite->Move(x, y);
					break;
			}
		}
		else if (sdlEvent.type == SDL_KEYUP || sdlEvent.type == SDL_KEYDOWN)
		{
			if (!m_bIsPaused)
			{
				m_PlayerCharacter->HandleInput(&sdlEvent);
			}
		}

		//m_ImGuiContext->HandleEvent(&sdlEvent);
	}
}

void RogueClient::Update(GameTimer* timer)
{
	// TODO: Additional update logic here.

	m_PlayerCharacter->Update(timer->GetDeltaTime());

	//m_ImGuiContext->Update();
}

void RogueClient::Clear()
{
	SDL_RenderClear(RenderImpl::Instance().GetRenderer());
}

void RogueClient::Draw()
{
	//m_ImGuiContext->Draw();

	m_DiagnosticText->Draw();
	m_PlayerCharacter->Draw();
}

void RogueClient::Present()
{
	SDL_RenderPresent(RenderImpl::Instance().GetRenderer());
}

void RogueClient::Exit()
{
	if (m_ImGuiContext != nullptr)
	{
		m_ImGuiContext->Destroy();
		m_ImGuiContext = nullptr;
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
