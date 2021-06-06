#include "Systems/InputManager.h"

InputManager& InputManager::Instance()
{
	static InputManager m_Instance;

	return m_Instance;
}

void InputManager::Update()
{
	m_KeyStates = const_cast<Uint8*>(SDL_GetKeyboardState(0));
}

bool InputManager::IsKeyDown(SDL_Scancode keycode) const
{
	if (m_KeyStates != nullptr)
	{
		return m_KeyStates[keycode] == 1;
	}
	return false;
}