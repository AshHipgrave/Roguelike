#include "RenderText.h"

RenderText::RenderText(SDL_Renderer* renderer, const char* fontName, const int fontSize, SDL_Color textColour)
{
	m_Renderer = renderer;

	m_TextFont = TTF_OpenFont(fontName, fontSize);

	if (!m_TextFont)
	{
		std::cout << "Failed to load required font! " << TTF_GetError() << std::endl;
		return;
	}
}

RenderText::RenderText(const char* text, int xPos, int yPos, SDL_Renderer* renderer, const char* fontName, const int fontSize, SDL_Color textColour)
{
	m_Renderer = renderer;

	m_TextFont = TTF_OpenFont(fontName, fontSize);

	if (!m_TextFont)
	{
		std::cout << "Failed to load required font! " << TTF_GetError() << std::endl;
		return;
	}

	m_TextSurface = TTF_RenderText_Blended(m_TextFont, text, textColour);

	m_TextTexture = SDL_CreateTextureFromSurface(renderer, m_TextSurface);

	m_DestRect = { xPos, yPos, m_TextSurface->w, m_TextSurface->h };
}

RenderText::~RenderText()
{
	if (m_TextTexture)
	{
		SDL_DestroyTexture(m_TextTexture);
	}

	if (m_TextSurface)
	{
		SDL_FreeSurface(m_TextSurface);
	}

	TTF_CloseFont(m_TextFont);
}

void RenderText::Draw()
{
	SDL_RenderCopy(m_Renderer, m_TextTexture, NULL, &m_DestRect);
}

void RenderText::SetText(const char* text, const char* fontName, const int fontSize, SDL_Color textColour)
{
	if (m_TextTexture)
	{
		SDL_DestroyTexture(m_TextTexture);
	}

	if (m_TextSurface)
	{
		SDL_FreeSurface(m_TextSurface);
	}

	m_TextSurface = TTF_RenderText_Blended(m_TextFont, text, textColour);

	m_TextTexture = SDL_CreateTextureFromSurface(m_Renderer, m_TextSurface);

	m_DestRect.w = m_TextSurface->w; 
	m_DestRect.h = m_TextSurface->h;
}

void RenderText::SetPosition(int xPos, int yPos)
{
	m_DestRect.x = xPos;
	m_DestRect.y = yPos;
}
