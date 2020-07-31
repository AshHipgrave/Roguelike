#pragma once

#include "Sprite.h"

struct SpriteFrame
{
	int width;
	int height;
	int x;
	int y;
};

class AnimSprite : public Sprite
{
public:
	AnimSprite(std::string imagePath, SpriteFrame frames[], int totalFrames, int fps, int width, int height, int x, int y, SDL_Renderer* renderer);

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;

private:
	int m_TotalFrames;
	int m_CurrentFrame;

	int m_AnimFPS;
	int m_CurrentFrameCount;

	SpriteFrame* m_AnimFrames = nullptr;

	SDL_Rect m_FrameRect = { 0, 0, 0, 0 };
};