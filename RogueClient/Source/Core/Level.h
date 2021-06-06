#pragma once

#include <map>
#include <string>
#include <vector>

#include <SDL.h>

#include <tmxlite\Map.hpp>
#include <tmxlite\TileLayer.hpp>

#include "Systems/RenderImpl.h"
#include "Systems/TextureManager.h"

struct Tile
{
	SDL_Texture* TileMap = nullptr;

	int X;
	int Y;

	int Tx;
	int Ty;

	int Width;
	int Height;

	Tile(SDL_Texture* tilemapTexture, int x = 0, int y = 0, int tx = 0, int ty = 0, int width = 0, int height = 0);

	void Draw();
};

class Level
{
public:
	Level(const std::string& levelName);

	void Load(const std::string& filePath);

	void Update(float deltaTime);
	void Draw();

private:
	std::string m_LevelName;

	int m_TotalRows;
	int m_TotalColumns;

	int m_TileWidth;
	int m_TileHeight;

	std::vector<Tile> m_Tiles;

	std::map<int, SDL_Texture*> m_Tilesets;
};

