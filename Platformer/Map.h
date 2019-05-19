#ifndef MAP_H
#define MAP_H

#include <map>

#include "Tile.h"

class Map
{
public:
	Map(const int& width, const int& height);
	~Map();

	static const int mTileSize = 32;

protected:
	int mWidth, mHeight;
	std::map<int, Tile*> mTiles;

public:
	bool IsSolid(int x, int y);
	bool IsEmpty(int x, int y);
	bool IsBoundary(int x, int y);

	bool IsBreakable(int x, int y);
	void BreakTile(int x, int y, int damage = 0, bool instant = false);

	bool Collides(PhysEntity* entity, int x, int y);

	virtual Vector2 Spawn() = 0;

	void Update();
	void Render();
};

#endif