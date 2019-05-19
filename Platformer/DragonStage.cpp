#include "DragonStage.h"

DragonStage::DragonStage()
	: Map(70, 16)
{
	Init();
}


DragonStage::~DragonStage()
{
}

void DragonStage::GenerateFloor()
{
	int y = 13;
	for (int i = mWidth * 0.17f; i < mWidth * 0.83f; i++)
	{
		mTiles[i + y * mWidth] = new Tile(new Texture("floor.png"), TileType::Breakable, i, y);
	}
}

void DragonStage::Init()
{
	GenerateFloor();
}

Vector2 DragonStage::Spawn()
{
	return Vector2(Graphics::SCREEN_WIDTH * 0.5f + mWidth * 0.33f * mTileSize, Graphics::SCREEN_HEIGHT * 0.75f);
}
