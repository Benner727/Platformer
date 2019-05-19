#include "Explosion.h"

#include "PhysicsManager.h"

Explosion::Explosion(Map* map, Vector2 pos)
	: Event(map, pos)
{
	mSprite = new AnimatedTexture("explosion.png", 0, 0, 60, 56, 8, 0.4f, AnimatedTexture::ANIM_DIR::horizontal);
	mSprite->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mSprite->Parent(this);

	Pos(pos);

	mMultiHit = true;
	mTerraform = true;
	mInstantBreak = true;

	mDamage = 350;

	AddCollider(new CircleCollider(mSprite->ScaledDimensions().x * 0.5f));

	mCollisionLayer = CollisionLayers::FriendlyProjectiles;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}

Explosion::~Explosion()
{
}

void Explosion::Hit(PhysEntity * other)
{
	mHit = true;
}

bool Explosion::CleanUp()
{
	return !(mSprite->IsAnimating());
}

void Explosion::Update()
{
	if (!mStarted)
	{
		mStarted = true;
		mAudio->PlaySFX("rumble.ogg", 0, 4);
	}

	if (mHit)
		Active(false);

	if (Active())
	{
		if (HasLeftWall() | HasRightWall() | HasCeiling() | HasGround() | InsideTile())
		{
			mHit = true;
		}
	}

	mSprite->Update();
}

void Explosion::Render()
{
	mSprite->Render();

	PhysEntity::Render();
}