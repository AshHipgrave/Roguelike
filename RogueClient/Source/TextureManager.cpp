#include "TextureManager.h"

TextureManager::~TextureManager()
{
	for (auto texture : m_LoadedTextures)
	{
		if (texture.second)
		{
			SDL_DestroyTexture(texture.second);
			texture.second = nullptr;
		}
	}
}

TextureManager& TextureManager::Instance()
{
	static TextureManager instance;

	return instance;
}

SDL_Texture* TextureManager::LoadTexture(const std::string& path)
{
	auto exists = m_LoadedTextures.find(path);

	if (exists != m_LoadedTextures.end())
	{
		return exists->second;
	}

	SDL_Surface* textureSurface = IMG_Load(path.c_str());

	if (textureSurface == nullptr)
	{
		std::cout << "Failed to load texture '" << path << "': " << SDL_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(RenderImpl::Instance().GetRenderer(), textureSurface);

	if (texture == nullptr)
	{
		std::cout << "Failed to create texture '" << path << "': " << SDL_GetError() << std::endl;
		return nullptr;
	}

	m_LoadedTextures.insert(std::pair<std::string, SDL_Texture*>(path, texture));

	return texture;
}
