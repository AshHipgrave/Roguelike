#include "RenderText.h"

RenderText::RenderText(const char* fontName, const int fontSize)
{
	m_TextFont = TTF_OpenFont(fontName, fontSize);

	if (!m_TextFont)
	{
		std::cout << "Failed to load required font! " << TTF_GetError() << std::endl;
		return;
	}
}

RenderText::~RenderText()
{
	Cleanup();

	m_TextSurface = nullptr;
	m_TextTexture = nullptr;
	m_TextFont = nullptr;
}

void RenderText::Cleanup()
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

void RenderText::Draw(const char* text, int xPos, int yPos, SDL_Renderer* renderer, SDL_Color textColor)
{
	Cleanup();

	m_TextSurface = TTF_RenderText_Solid(m_TextFont, text, textColor);

	m_TextTexture = SDL_CreateTextureFromSurface(renderer, m_TextSurface);

	SDL_Rect dest = { xPos, yPos, m_TextSurface->w, m_TextSurface->h };

	SDL_RenderCopy(renderer, m_TextTexture, NULL, &dest);
}
