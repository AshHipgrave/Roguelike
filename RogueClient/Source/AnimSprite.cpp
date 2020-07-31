#include "AnimSprite.h"

AnimSprite::AnimSprite(std::string imagePath, SpriteFrame frames[], int totalFrames, int fps, int width, int height, int x, int y, SDL_Renderer* renderer)
	: Sprite(imagePath, width, height, x, y, renderer)
{
	m_AnimFrames = frames;
	m_TotalFrames = totalFrames;

	m_CurrentFrame = 0;
	m_CurrentFrameCount = 0;

	SpriteFrame* firstFrame = &m_AnimFrames[m_CurrentFrame];

	m_FrameRect.x = firstFrame->x;
	m_FrameRect.y = firstFrame->y;

	m_FrameRect.w = firstFrame->width;
	m_FrameRect.h = firstFrame->height;

	m_AnimFPS = fps;
}

void AnimSprite::Update(float deltaTime)
{
	m_CurrentFrameCount++;

	if (m_CurrentFrameCount >= m_AnimFPS)
	{
		m_CurrentFrame++;
		m_CurrentFrame %= m_TotalFrames;

		SpriteFrame* currentFrame = &m_AnimFrames[m_CurrentFrame];

		m_FrameRect.x = currentFrame->x;
		m_FrameRect.y = currentFrame->y;

		m_FrameRect.w = currentFrame->width;
		m_FrameRect.h = currentFrame->height;

		m_CurrentFrameCount = 0;
	}
}

void AnimSprite::Draw()
{
	SDL_RenderCopy(m_Renderer, m_SpriteTexture, &m_FrameRect, &m_SpriteRect);
}
