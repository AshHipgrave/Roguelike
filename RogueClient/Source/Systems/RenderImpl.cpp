#include "Systems/RenderImpl.h"

RenderImpl& RenderImpl::Instance()
{
	static RenderImpl m_Instance;

	return m_Instance;
}

bool RenderImpl::Init()
{
	GameWindow& gameWindow = GameWindow::Instance();

	m_Renderer = SDL_CreateRenderer(gameWindow.GetGameWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	m_RenderResolutionWidth = gameWindow.GetWindowWidth() / 2;
	m_RenderResolutionHeight = gameWindow.GetWindowHeight() / 2;
	
	SDL_RenderSetLogicalSize(m_Renderer, m_RenderResolutionWidth, m_RenderResolutionHeight);

	return m_Renderer != nullptr;
}

int RenderImpl::GetRenderWidth() const
{
	return m_RenderResolutionWidth;
}

int RenderImpl::GetRenderHeight() const
{
	return m_RenderResolutionHeight;
}

SDL_Renderer* RenderImpl::GetRenderer() const
{
	return m_Renderer;
}