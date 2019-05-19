#include "DemonStage.h"

DemonStage::DemonStage()
	: Map(550, 16)
{
	Init();
}


DemonStage::~DemonStage()
{
}

void DemonStage::GenerateFloor()
{
	int y = 13;
	for (int i = 0; i < mWidth * 0.9f; i++)
	{
		mTiles[i + y * mWidth] = new Tile(new Texture("floor.png"), TileType::Solid, i, y);
	}
}

void DemonStage::GenerateObstacles()
{
	int y = 13;
	int j = 0, k = 0, l = 0;
	for (int i = 0; i < mWidth* 0.9f; i++)
	{
		if (j > 20)
		{
			mTiles[i + (y - 4) * mWidth] = new Tile(new Texture("floor.png"), TileType::Breakable, i, y - 4);

			if (j > 25 || !(rand() % 5))
				j = 0;
		}

		if (k > 10 && !(rand() % 5))
		{
			mTiles[i + (y - 1) * mWidth] = new Tile(new Texture("floor.png"), TileType::Breakable, i, y - 1);

			if (rand() % 2)
			{
				mTiles[i + (y - 2) * mWidth] = new Tile(new Texture("floor.png"), TileType::Breakable, i, y - 2);

				if (rand() % 2)
					mTiles[i + (y - 3) * mWidth] = new Tile(new Texture("floor.png"), TileType::Breakable, i, y - 3);
			}

			k = 0;
		}

		if (l > 15 && !(rand() % 2))
		{
			mTiles[i + (y - 8) * mWidth] = new Tile(new Texture("floor.png"), TileType::Breakable, i, y - 8);

			if (rand() % 2)
				l = 0;
		}

		j++;
		k++;
		l++;
	}
}

void DemonStage::Init()
{
	GenerateFloor();
	GenerateObstacles();
}

Vector2 DemonStage::Spawn()
{
	return Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.33f);
}