#include "RenderText.h"

RenderText::RenderText(SDL_Renderer* renderer)
{
	m_Renderer = renderer;
}

RenderText::RenderText(const char* text, int xPos, int yPos, SDL_Renderer* renderer, const char* fontName, const int fontSize, SDL_Color textColour)
{
	m_Renderer = renderer;

	TTF_Font* textFont = TTF_OpenFont(fontName, fontSize);

	m_TextSurface = TTF_RenderText_Blended(textFont, text, textColour);
	m_TextTexture = SDL_CreateTextureFromSurface(renderer, m_TextSurface);

	m_DestRect.x = xPos;
	m_DestRect.y = yPos;

	m_DestRect.w = m_TextSurface->w;
	m_DestRect.h = m_TextSurface->h;

	TTF_CloseFont(textFont);
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

	TTF_Font* textFont = TTF_OpenFont(fontName, fontSize);

	m_TextSurface = TTF_RenderText_Blended(textFont, text, textColour);
	m_TextTexture = SDL_CreateTextureFromSurface(m_Renderer, m_TextSurface);

	m_DestRect.w = m_TextSurface->w; 
	m_DestRect.h = m_TextSurface->h;

	TTF_CloseFont(textFont);
}

void RenderText::SetPosition(int xPos, int yPos)
{
	m_DestRect.x = xPos;
	m_DestRect.y = yPos;
}
