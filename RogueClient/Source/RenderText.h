#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>

class RenderText
{
public:
	RenderText(const char* fontName = "C:\\Windows\\Fonts\\arial.ttf", const int fontSize = 18);
	~RenderText();

	void Draw(const char* text, int xPos, int yPos, SDL_Renderer* renderer, SDL_Color textColour = { 0, 0, 0 });

protected:
	void Cleanup();

private:
	TTF_Font* m_TextFont = nullptr;

	SDL_Surface* m_TextSurface = nullptr;
	SDL_Texture* m_TextTexture = nullptr;
};

