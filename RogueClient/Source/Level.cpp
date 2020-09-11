#include "Level.h"

#include <math.h>

Tile::Tile(SDL_Texture* tilemapTexture, int x, int y, int tx, int ty, int width, int height)
	: TileMap(tilemapTexture), X(x), Y(y), Tx(tx), Ty(ty), Width(width), Height(height)
{
}

void Tile::Draw()
{
	if (TileMap == nullptr || (X > GameWindow::Instance().GetWindowWidth() || Y > GameWindow::Instance().GetWindowHeight()))
		return;

	static int drawCall = 0;

	SDL_Rect src;
	
	src.x = Tx;
	src.y = Ty;

	src.w = Width;
	src.h = Height;

	SDL_Rect dest;
	dest.x = X;
	dest.y = Y;
	dest.w = src.w;
	dest.h = src.h;
	
	SDL_RenderCopy(RenderImpl::Instance().GetRenderer(), TileMap, &src, &dest);
}

Level::Level(const std::string& levelName)
	: m_LevelName(levelName), m_TotalRows(0), m_TotalColumns(0), m_TileHeight(0), m_TileWidth(0)
{
}

void Level::Load(const std::string& filePath)
{
	tmx::Map levelMap;
	levelMap.load(filePath);

	const tmx::Vector2u mapDimensions = levelMap.getTileCount();

	m_TotalRows = mapDimensions.y;
	m_TotalColumns = mapDimensions.x;

	const tmx::Vector2u tileSize = levelMap.getTileSize();

	m_TileWidth = tileSize.x;
	m_TileHeight = tileSize.y;

	const std::vector<tmx::Tileset>& tilesets = levelMap.getTilesets();

	for (auto& tileset : tilesets)
	{
		SDL_Texture* tilesetTexture = TextureManager::Instance().LoadTexture(tileset.getImagePath());

		m_Tilesets.insert(std::pair<int, SDL_Texture*>(tileset.getFirstGID(), tilesetTexture));
	}

	const std::vector<tmx::Layer::Ptr>& layers = levelMap.getLayers();

	for (auto& layer : layers)
	{
		if (layer->getType() != tmx::Layer::Type::Tile)
			continue;

		const tmx::TileLayer* tileLayer = dynamic_cast<const tmx::TileLayer*>(layer.get());

		auto& layerTiles = tileLayer->getTiles();

		for (int y = 0; y < m_TotalRows; y++)
		{
			for (int x = 0; x < m_TotalColumns; x++)
			{
				int tileIndex = x + (y * m_TotalColumns);

				int currentGid = layerTiles[tileIndex].ID;

				if (currentGid == 0)
					continue;

				int tilesetGid = -1;

				for (auto& tileset : m_Tilesets)
				{
					if (tileset.first <= currentGid)
					{
						tilesetGid = tileset.first;
						break;
					}
				}

				if (tilesetGid == -1)
					continue;

				currentGid -= tilesetGid;

				int tilesetWidth = 0;
				int tilesetHeight = 0;

				SDL_QueryTexture(m_Tilesets[tilesetGid], NULL, NULL, &tilesetWidth, &tilesetHeight);

				int spacing = 1;

				int spritesPerRow = ((tilesetWidth + spacing) / (m_TileWidth + spacing));

				int regionX = (currentGid % spritesPerRow) * (m_TileWidth + spacing);
				int regionY = (currentGid / spritesPerRow) * (m_TileHeight + spacing);

				int xPosition = x * m_TileWidth;
				int yPosition = y * m_TileHeight;

				Tile tile(m_Tilesets[tilesetGid], xPosition, yPosition, regionX, regionY, m_TileWidth, m_TileHeight);
				m_Tiles.push_back(tile);
			}
		}
	}
}

void Level::Update(float deltaTime)
{
}

void Level::Draw()
{
	for (Tile tile : m_Tiles)
	{
		tile.Draw();
	}
}