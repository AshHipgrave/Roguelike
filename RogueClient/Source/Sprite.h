#pragma once

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "RenderImpl.h"

class Sprite
{
public:
	Sprite(std::string imagePath, int width, int height, int x, int y);

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Destroy();

	int GetX();
	int GetY();

	int GetWidth();
	int GetHeight();

	void Move(int newX, int newY);
	void Resize(int newWidth, int newHeight);

protected:
	SDL_Texture* m_SpriteTexture = nullptr;

	SDL_Rect m_SpriteRect = { 0, 0, 0, 0 };
};

