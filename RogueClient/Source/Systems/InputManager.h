#pragma once

#include <SDL.h>

class InputManager
{
public:
	static InputManager& Instance();

public:
	void Update();

	bool IsKeyDown(SDL_Scancode keycode) const;

private:
	Uint8* m_KeyStates = nullptr;

private:
	InputManager() { }
};

