#include "Map.h"

Map::Map(const int& width, const int& height)
	: mWidth(width), mHeight(height)
{
}


Map::~Map()
{
	for (auto tile : mTiles)
	{
		if (tile.second != nullptr)
			delete tile.second;
	}
	mTiles.clear();
}

bool Map::IsSolid(int x, int y)
{
	if (x < 0 || y < 0)
		return false;

	if (mTiles[x + y * mWidth] != nullptr)
		return (mTiles[x + y * mWidth]->GetType() == TileType::Solid || mTiles[x + y * mWidth]->GetType() == TileType::Breakable);

	return false;
}

bool Map::IsEmpty(int x, int y)
{
	if (x < 0 || y < 0)
		return false;

	if (mTiles[x + y * mWidth] != nullptr)
		return (mTiles[x + y * mWidth]->GetType() == TileType::Empty);

	return true;
}

bool Map::IsBoundary(int x, int y)
{
	if (x >= mWidth || y >= mHeight)
		return true;

	return false;
}

bool Map::IsBreakable(int x, int y)
{
	if (x < 0 || x >= mWidth
		|| y < 0 || y >= mHeight)
		return false;

	if (mTiles[x + y * mWidth] != nullptr)
		return (mTiles[x + y * mWidth]->GetType() == TileType::Breakable);

	return false;
}

void Map::BreakTile(int x, int y, int damage, bool instant)
{
	if (IsBreakable(x, y))
		mTiles[x + y * mWidth]->Break(damage, instant);
}

bool Map::Collides(PhysEntity * entity, int x, int y)
{
	if (x < 0 || x >= mWidth
		|| y < 0 || y >= mHeight)
		return true;

	return (mTiles[x + y * mWidth]->CheckCollision(entity));
}

void Map::Update()
{
	for (auto& tile : mTiles)
	{
		if (tile.second != nullptr)
		{
			tile.second->Update();

			if (tile.second->Broken())
			{
				delete tile.second;
				tile.second = nullptr;
			}
		}
	}
}

void Map::Render()
{
	for (const auto& tile : mTiles)
	{
		if (tile.second != nullptr)
			tile.second->Render();
	}
}
