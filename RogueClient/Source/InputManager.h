#pragma once

#include <SDL.h>

class InputManager
{
public:
	static InputManager& Instance()
	{
		static InputManager m_Instance;

		return m_Instance;
	}

public:
	void Update()
	{
		m_KeyStates = const_cast<Uint8*>(SDL_GetKeyboardState(0));
	}

	bool IsKeyDown(SDL_Scancode keycode)
	{
		if (m_KeyStates != nullptr)
		{
			return m_KeyStates[keycode] == 1;
		}
		return false;
	}

private:
	Uint8* m_KeyStates = nullptr;

private:
	InputManager() { }
};

