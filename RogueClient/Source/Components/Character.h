#pragma once

#include <SDL.h>

#include <map>
#include <utility>

#include "Math/Vector2f.h"
#include "Core/GameTimer.h"
#include "Systems/InputManager.h"
#include "Components/AnimSprite.h"

class Character
{
public:
	Character(int x, int y);

	void HandleInput();

	void Update(float deltaTime);

	void Draw();

private:
	AnimSprite* m_CharacterSprite = nullptr;

private:
	Vector2f m_Velocity;
	Vector2f m_Position;

	const float MovementSpeed = 0.2f;

private:
	AnimationFrame WalkDownAnimationFrames[4] =
	{
		{ 15, 22, 1, 6 },
		{ 15, 22, 17, 6 },
		{ 15, 22, 33, 6 },
		{ 15, 22, 49, 6 }
	};

	AnimationFrame WalkRightAnimationFrames[4] =
	{
		{ 15, 22, 2, 38 }, 
		{ 15, 22, 18, 38 }, 
		{ 15, 22, 34, 38 }, 
		{ 15, 22, 50, 38 }
	};

	AnimationFrame WalkUpAnimationFrames[4] =
	{
		{ 15, 23, 0, 69 }, 
		{ 15, 23, 16, 69 }, 
		{ 15, 23, 32, 69 }, 
		{ 15, 23, 48, 69 }
	};
	
	AnimationFrame WalkLeftAnimationFrames[4] =
	{
		{ 15, 23, 1, 102 }, 
		{ 15, 22, 17, 102 }, 
		{ 15, 22, 33, 102 }, 
		{ 15, 22, 49, 102 }
	};

private:
	Animation WalkDownAnimation =
	{
		4,
		30.0f,
		WalkDownAnimationFrames
	};

	Animation WalkRightAnimation =
	{
		4,
		30.0f,
		WalkRightAnimationFrames
	};

	Animation WalkUpAnimation =
	{
		4,
		30.0f,
		WalkUpAnimationFrames
	};

	Animation WalkLeftAnimation =
	{
		4,
		30.0f,
		WalkLeftAnimationFrames
	};
};