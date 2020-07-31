#include "Sprite.h"

Sprite::Sprite(std::string imagePath, int width, int height, int x, int y, SDL_Renderer* renderer)
{
	m_Renderer = renderer;

	SDL_Surface* spriteSurface = IMG_Load(imagePath.c_str());

	m_SpriteTexture = SDL_CreateTextureFromSurface(m_Renderer, spriteSurface);

	m_SpriteRect = { x, y, width, height };

	SDL_FreeSurface(spriteSurface);
}

void Sprite::Update(float deltaTime)
{
}

void Sprite::Draw()
{
	SDL_RenderCopy(m_Renderer, m_SpriteTexture, NULL, &m_SpriteRect);
}

void Sprite::Destroy()
{
	if (m_SpriteTexture)
	{
		SDL_DestroyTexture(m_SpriteTexture);
		m_SpriteTexture = nullptr;
	}
}

int Sprite::GetX()
{
	return m_SpriteRect.x;
}

int Sprite::GetY()
{
	return m_SpriteRect.y;
}

int Sprite::GetWidth()
{
	return m_SpriteRect.w;
}

int Sprite::GetHeight()
{
	return m_SpriteRect.h;
}

void Sprite::Move(int newX, int newY)
{
	m_SpriteRect.x = newX;
	m_SpriteRect.y = newY;
}

void Sprite::Resize(int newWidth, int newHeight)
{
	m_SpriteRect.w = newWidth;
	m_SpriteRect.h = newHeight;
}
