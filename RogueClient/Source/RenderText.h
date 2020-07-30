#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>

class RenderText
{
public:
	RenderText(SDL_Renderer* renderer);
	RenderText(const char* text, int xPos, int yPos, SDL_Renderer* renderer, const char* fontName = "C:\\Windows\\Fonts\\arial.ttf", const int fontSize = 18, SDL_Color textColour = { 0, 0, 0, 255 });
	
	~RenderText();

	void Draw();

	void SetText(const char* text, const char* fontName = "C:\\Windows\\Fonts\\arial.ttf", const int fontSize = 18, SDL_Color textColour = { 0, 0, 0, 255 });
	void SetPosition(int xPos, int yPos);

private:
	SDL_Renderer* m_Renderer = nullptr;

	SDL_Surface* m_TextSurface = nullptr;
	SDL_Texture* m_TextTexture = nullptr;

private:
	SDL_Rect m_DestRect = { 0, 0, 0, 0 };
};

