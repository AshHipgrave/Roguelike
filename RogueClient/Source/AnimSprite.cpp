#include "AnimSprite.h"

AnimSprite::AnimSprite(std::string imagePath, std::map<std::string, Animation> animations, std::string startState, int width, int height, int x, int y, SDL_Renderer* renderer)
	: Sprite(imagePath, width, height, x, y, renderer) 
{
	m_SpriteAnimations = animations;

	m_CurrentState = startState;
	
	Reset();
}

void AnimSprite::Update(float deltaTime)
{
	if (!m_bIsIdle)
	{
		m_CurrentFrameDrawCount++;

		if (m_CurrentFrameDrawCount >= m_AnimFPS)
		{
			Animation* currentAnimation = &m_SpriteAnimations[m_CurrentState];

			m_CurrentFrameIdx++;
			m_CurrentFrameIdx %= currentAnimation->FrameCount;

			AnimationFrame* nextFrame = &currentAnimation->Frames[m_CurrentFrameIdx];

			m_FrameRect.x = nextFrame->X;
			m_FrameRect.y = nextFrame->Y;

			m_FrameRect.w = nextFrame->Width;
			m_FrameRect.h = nextFrame->Height;

			m_CurrentFrameDrawCount = 0;
		}
	}
}

void AnimSprite::Draw()
{
	SDL_RenderCopy(m_Renderer, m_SpriteTexture, &m_FrameRect, &m_SpriteRect);
}

void AnimSprite::SetState(std::string state)
{
	if (m_CurrentState.compare(state) == 0 && !m_bIsIdle) return; // No state change

	m_CurrentState = state;

	Animation* newState = &m_SpriteAnimations[m_CurrentState];
	m_AnimFPS = newState->FramesPerSecond;

	m_bIsIdle = false;

	Reset();
}

std::string AnimSprite::GetState() const
{
	return m_CurrentState;
}

void AnimSprite::SetIdle(bool isIdle)
{
	m_bIsIdle = isIdle;

	Reset();
}

void AnimSprite::Reset()
{
	m_CurrentFrameIdx = 0;
	m_CurrentFrameDrawCount = 0;

	Animation* currentAnimation = &m_SpriteAnimations[m_CurrentState];

	AnimationFrame* currentFrame = &currentAnimation->Frames[m_CurrentFrameIdx];

	m_FrameRect.x = currentFrame->X;
	m_FrameRect.y = currentFrame->Y;

	m_FrameRect.w = currentFrame->Width;
	m_FrameRect.h = currentFrame->Height;

	m_AnimFPS = currentAnimation->FramesPerSecond;
}
