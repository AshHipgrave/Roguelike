#include "RogueClient.h"

bool RogueClient::Init(const char* windowTitle, int windowWidth, int windowHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return false;

	if (TTF_Init() != 0)
		return false;

	m_GameWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	SDL_SetWindowResizable(m_GameWindow, SDL_bool::SDL_TRUE);

	if (m_GameWindow == nullptr)
		return false;

	m_Renderer = SDL_CreateRenderer(m_GameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	ImGui::CreateContext();
	ImGuiSDL::Initialize(m_Renderer, windowWidth, windowHeight);

	SDL_SetRenderDrawColor(m_Renderer, 100, 149, 237, 255);

	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);

	LoadResources();

	return true;
}

void RogueClient::LoadResources()
{
	m_DiagnosticText = new RenderText(m_Renderer);
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
			ImGuiDraw();
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

				case SDL_WINDOWEVENT_SIZE_CHANGED:
					ImGuiIO& io = ImGui::GetIO();

					io.DisplaySize.x = static_cast<float>(sdlEvent.window.data1);
					io.DisplaySize.y = static_cast<float>(sdlEvent.window.data2);
					
					break;
			}
		}
		else if (sdlEvent.type == SDL_MOUSEWHEEL)
		{
			ImGuiIO& io = ImGui::GetIO();
			io.MouseWheel = static_cast<float>(sdlEvent.wheel.y);
		}
	}
}

void RogueClient::Update(GameTimer* timer)
{
	int mouseX, mouseY;

	const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

	ImGuiIO& io = ImGui::GetIO();

	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

	// TODO: Update logic here.
}

void RogueClient::Clear()
{
	SDL_RenderClear(m_Renderer);
}

void RogueClient::Draw()
{
	m_DiagnosticText->Draw();

	//TODO: Additional draw logic here.	
}

void RogueClient::Present()
{
	SDL_RenderPresent(m_Renderer);
}

void RogueClient::ImGuiDraw()
{
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
}

void RogueClient::Exit()
{
	ImGuiSDL::Deinitialize();
	ImGui::DestroyContext();

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
