#ifndef TILE_H
#define TILE_H

#include "AnimatedTexture.h"
#include "PhysEntity.h"

enum class TileType { Empty = 0, Solid, Breakable, Boundary };

class Tile : public PhysEntity
{
public:
	Tile();
	Tile(Texture* tex, TileType type, int x, int y);
	~Tile();

	static const int mTileSize = 32;

private:
	Texture* mSprite;
	AnimatedTexture* mDeath;

	TileType mType;

	int mTileNum;

public:
	TileType GetType() const;

	void InstantBreak();
	void Break(int damage, bool instant = false);
	bool Broken() const;

	void Update();
	void Render();
};

#endif