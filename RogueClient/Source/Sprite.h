#pragma once

#include <string>

#include <SDL.h>
#include <SDL_image.h>

class Sprite
{
public:
	Sprite(std::string imagePath, int width, int height, int x, int y, SDL_Renderer* renderer);

	void Update(float deltaTime);
	void Draw();

	void Destroy();

	int GetX();
	int GetY();

	int GetWidth();
	int GetHeight();

	void Move(int newX, int newY);
	void Resize(int newWidth, int newHeight);

private:
	SDL_Renderer* m_Renderer = nullptr;

	SDL_Texture* m_SpriteTexture = nullptr;

private:
	SDL_Rect m_SpriteRect = { 0, 0, 0, 0 };
};

