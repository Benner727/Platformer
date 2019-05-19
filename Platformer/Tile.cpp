#include "Tile.h"

#include "BoxCollider.h"

Tile::Tile()
{
	mSprite = nullptr;
	mDeath = nullptr;
	mType = TileType::Empty;
	mHealth = 1;
	mTileNum = -1;
}

Tile::Tile(Texture * tex, TileType type, int x, int y)
{
	mSprite = tex;
	mSprite->Parent(this);

	mType = type;

	if (mType == TileType::Breakable)
	{
		mDeath = new AnimatedTexture("crumble.png", 0, 0, 32, 32, 3, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
		mDeath->WrapMode(AnimatedTexture::WRAP_MODE::once);
		mDeath->Parent(this);
	}

	mHealth = 150;
	mTileNum = 0;

	Pos(Vector2(x * mTileSize + mTileSize * 0.5f, y * mTileSize + mTileSize * 0.5f));

	AddCollider(new BoxCollider(mSprite->ScaledDimensions()));
}

Tile::~Tile()
{
	delete mSprite;
	delete mDeath;
}

TileType Tile::GetType() const
{
	return mType;
}

void Tile::InstantBreak()
{
	mHealth = 0; 
	mTileNum = 1;
}

void Tile::Break(int damage, bool instant)
{
	if (instant)
		InstantBreak();

	if (mHealth <= 125 && mTileNum == 0)
	{
		Vector2 prevPos = mSprite->Pos();
		delete mSprite;
		mSprite = new Texture("brokenfloor1.png");
		mSprite->Pos(prevPos);
		mSprite->Parent(this);
		mTileNum++;
	}
	else if (mHealth <= 50 && mTileNum == 1)
	{
		Vector2 prevPos = mSprite->Pos();
		delete mSprite;
		mSprite = new Texture("brokenfloor2.png");
		mSprite->Pos(prevPos);
		mSprite->Parent(this);
		mTileNum++;
	}
	else if (mHealth <= 0 && mTileNum == 2)
		mType = TileType::Empty;

	mHealth -= damage;
}

bool Tile::Broken() const
{
	if (mDeath != nullptr)
	{
		return (!mDeath->IsAnimating());
	}

	return false;
}

void Tile::Update()
{
	if (mHealth <= 0)
		mDeath->Update();
}

void Tile::Render()
{
	if (mSprite != nullptr)
	{
		if (mHealth <= 0)
			mDeath->Render();
		else
			mSprite->Render();

		PhysEntity::Render();
	}
}
