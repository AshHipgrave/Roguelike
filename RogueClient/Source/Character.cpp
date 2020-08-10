#include "Character.h"

Character::Character(int x, int y)
{
	static std::map<std::string, Animation> characterAnimations;

	characterAnimations["WalkDown"] = WalkDownAnimation;
	characterAnimations["WalkRight"] = WalkRightAnimation;
	characterAnimations["WalkUp"] = WalkUpAnimation;
	characterAnimations["WalkLeft"] = WalkLeftAnimation;

	m_CharacterSprite = new AnimSprite("Assets\\Images\\SpriteSheet_Character.png", characterAnimations, "WalkDown", 60, 88, x, y);
	m_CharacterSprite->SetIdle(true);

	m_XPosition = x;
	m_YPosition = y;
}

void Character::HandleInput(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
			case SDLK_w:
				m_CharacterSprite->SetState("WalkUp");
				m_YPosition -= MovementSpeed;
				break;
			case SDLK_s:
				m_CharacterSprite->SetState("WalkDown");
				m_YPosition += MovementSpeed;
				break;
			case SDLK_a:
				m_CharacterSprite->SetState("WalkLeft");
				m_XPosition -= MovementSpeed;
				break;
			case SDLK_d:
				m_CharacterSprite->SetState("WalkRight");
				m_XPosition += MovementSpeed;
				break;
			default:
				break;
		}
	}
	else if (event->type == SDL_KEYUP)
	{
		m_CharacterSprite->SetIdle(true);
	}
}

void Character::Update(float deltaTime)
{
	m_CharacterSprite->Update(deltaTime);

	m_CharacterSprite->Move(m_XPosition, m_YPosition);
}

void Character::Draw()
{
	m_CharacterSprite->Draw();
}
