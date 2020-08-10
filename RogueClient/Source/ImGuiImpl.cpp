#include "ImGuiImpl.h"

void ImGuiImpl::Init(int windowWidth, int windowHeight)
{
	ImGui::CreateContext();
	ImGuiSDL::Initialize(RenderImpl::Instance().GetRenderer(), windowWidth, windowHeight);

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
	io.BackendPlatformName = "imgui_impl_sdl";

	io.KeyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
	io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
	io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
	io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
	io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
	io.KeyMap[ImGuiKey_Insert] = SDL_SCANCODE_INSERT;
	io.KeyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = SDL_SCANCODE_SPACE;
	io.KeyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;
	io.KeyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;
	io.KeyMap[ImGuiKey_KeyPadEnter] = SDL_SCANCODE_KP_ENTER;
	io.KeyMap[ImGuiKey_A] = SDL_SCANCODE_A;
	io.KeyMap[ImGuiKey_C] = SDL_SCANCODE_C;
	io.KeyMap[ImGuiKey_V] = SDL_SCANCODE_V;
	io.KeyMap[ImGuiKey_X] = SDL_SCANCODE_X;
	io.KeyMap[ImGuiKey_Y] = SDL_SCANCODE_Y;
	io.KeyMap[ImGuiKey_Z] = SDL_SCANCODE_Z;

	io.SetClipboardTextFn = SetClipboardText;
	io.GetClipboardTextFn = GetClipboardText;
	io.ClipboardUserData = NULL;

	m_MouseCursors[ImGuiMouseCursor_Arrow] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	m_MouseCursors[ImGuiMouseCursor_TextInput] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
	m_MouseCursors[ImGuiMouseCursor_ResizeAll] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
	m_MouseCursors[ImGuiMouseCursor_ResizeNS] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
	m_MouseCursors[ImGuiMouseCursor_ResizeEW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
	m_MouseCursors[ImGuiMouseCursor_ResizeNESW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
	m_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
	m_MouseCursors[ImGuiMouseCursor_Hand] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	m_MouseCursors[ImGuiMouseCursor_NotAllowed] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);

	m_bIsInitialised = true;
}

void ImGuiImpl::Destroy()
{
	m_bIsInitialised = false;
	
	ImGuiSDL::Deinitialize();
	ImGui::DestroyContext();
}

void ImGuiImpl::HandleEvent(SDL_Event* sdlEvent)
{
	ImGuiIO& io = ImGui::GetIO();

	if (sdlEvent->type == SDL_WINDOWEVENT)
	{
		switch (sdlEvent->window.event)
		{
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				ImGuiIO& io = ImGui::GetIO();

				io.DisplaySize.x = static_cast<float>(sdlEvent->window.data1);
				io.DisplaySize.y = static_cast<float>(sdlEvent->window.data2);

				break;
		}
	}
	else if (sdlEvent->type == SDL_MOUSEWHEEL)
	{
		io.MouseWheel = static_cast<float>(sdlEvent->wheel.y);
	}
	else if (sdlEvent->type == SDL_MOUSEBUTTONDOWN)
	{
		if (sdlEvent->button.button == SDL_BUTTON_LEFT) m_MouseButtonPressed[0] = true;
		if (sdlEvent->button.button == SDL_BUTTON_RIGHT) m_MouseButtonPressed[1] = true;
		if (sdlEvent->button.button == SDL_BUTTON_MIDDLE) m_MouseButtonPressed[2] = true;
	}
	else if (sdlEvent->type == SDL_TEXTINPUT)
	{
		io.AddInputCharactersUTF8(sdlEvent->text.text);
	}
	else if (sdlEvent->type == SDL_KEYDOWN || sdlEvent->type == SDL_KEYUP)
	{
		int keyCode = sdlEvent->key.keysym.scancode;

		io.KeysDown[keyCode] = (sdlEvent->type == SDL_KEYDOWN);

		io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
		io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
		io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
	}
}

void ImGuiImpl::Update()
{
	int mouseX, mouseY;

	const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

	ImGuiIO& io = ImGui::GetIO();

	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));

	io.MouseDown[0] = m_MouseButtonPressed[0] || buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = m_MouseButtonPressed[0] || buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	io.MouseDown[2] = m_MouseButtonPressed[0] || buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE);

	m_MouseButtonPressed[0] = m_MouseButtonPressed[1] = m_MouseButtonPressed[2] = false;
}

void ImGuiImpl::Draw()
{
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
}

bool ImGuiImpl::IsInitialised()
{
	return m_bIsInitialised;
}

const char* ImGuiImpl::GetClipboardText(void*)
{
	return SDL_GetClipboardText();
}

void ImGuiImpl::SetClipboardText(void*, const char* text)
{
	SDL_SetClipboardText(text);
}
