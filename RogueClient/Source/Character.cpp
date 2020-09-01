#include "Character.h"

#include <iostream>

Character::Character(int x, int y)
{
	static std::map<std::string, Animation> characterAnimations;

	characterAnimations["WalkDown"] = WalkDownAnimation;
	characterAnimations["WalkRight"] = WalkRightAnimation;
	characterAnimations["WalkUp"] = WalkUpAnimation;
	characterAnimations["WalkLeft"] = WalkLeftAnimation;

	m_CharacterSprite = new AnimSprite("Assets\\Images\\SpriteSheet_Character.png", characterAnimations, "WalkDown", 60, 88, x, y);
	m_CharacterSprite->SetIdle(true);

	m_Position.X = x;
	m_Position.Y = y;
}

void Character::HandleInput(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
			case SDLK_w:
				m_Velocity.Y = -MovementSpeed;
				m_CharacterSprite->SetState("WalkUp");
				break;
			case SDLK_s:
				m_Velocity.Y = MovementSpeed;
				m_CharacterSprite->SetState("WalkDown");
				break;
			case SDLK_a:
				m_Velocity.X = -MovementSpeed;
				m_CharacterSprite->SetState("WalkLeft");
				break;
			case SDLK_d:
				m_Velocity.X = MovementSpeed;
				m_CharacterSprite->SetState("WalkRight");
				break;
			default:
				break;
		}
	}
	else if (event->type == SDL_KEYUP)
	{
		m_Velocity.X = 0;
		m_Velocity.Y = 0;

		m_CharacterSprite->SetIdle(true);
	}
}

void Character::Update(float deltaTime)
{
	m_CharacterSprite->Update(deltaTime);

	m_Position += m_Velocity;

	m_CharacterSprite->Move(m_Position.X, m_Position.Y);
}

void Character::Draw()
{
	m_CharacterSprite->Draw();
}
