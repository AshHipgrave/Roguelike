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

	m_Position.X = x;
	m_Position.Y = y;
}

void Character::HandleInput()
{
	InputManager& inputManager = InputManager::Instance();

	m_Velocity.X = 0.0f;
	m_Velocity.Y = 0.0f;

	if (inputManager.IsKeyDown(SDL_SCANCODE_W))
	{
		m_Velocity.Y = -MovementSpeed;
		m_CharacterSprite->SetState("WalkUp");
	}
	else if (inputManager.IsKeyDown(SDL_SCANCODE_S))
	{
		m_Velocity.Y = MovementSpeed;
		m_CharacterSprite->SetState("WalkDown");
	}
	else if (inputManager.IsKeyDown(SDL_SCANCODE_A))
	{
		m_Velocity.X = -MovementSpeed;
		m_CharacterSprite->SetState("WalkLeft");
	}
	else if (inputManager.IsKeyDown(SDL_SCANCODE_D))
	{
		m_Velocity.X = MovementSpeed;
		m_CharacterSprite->SetState("WalkRight");
	}
}

void Character::Update(float deltaTime)
{
	HandleInput();

	m_CharacterSprite->Update(deltaTime);

	if (m_Velocity.X != 0.0f || m_Velocity.Y != 0.0f)
	{
		m_Position += m_Velocity;

		m_CharacterSprite->Move(m_Position.X, m_Position.Y);
	}
	else if (!m_CharacterSprite->IsIdle())
	{
		m_CharacterSprite->SetIdle(true);
	}
}

void Character::Draw()
{
	m_CharacterSprite->Draw();
}
