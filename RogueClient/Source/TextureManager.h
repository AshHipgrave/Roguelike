#pragma once

#include <map>
#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "RenderImpl.h"

class TextureManager
{
public:
	~TextureManager();

	static TextureManager& Instance();

	SDL_Texture* LoadTexture(const std::string& path);

private:
	std::map<std::string, SDL_Texture*> m_LoadedTextures;

private:
	TextureManager() { }
};