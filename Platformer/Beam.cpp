#include "Beam.h"

#include "PhysicsManager.h"
#include "ProjectileManager.h"

Beam::Beam(Map* map, Vector2 pos, float rotation, bool first)
	: Projectile(map, pos, rotation)
{
	mSprite = new AnimatedTexture("beam.png", 0, 0, 8, 8, 2, 0.1f, AnimatedTexture::ANIM_DIR::horizontal);
	//mSprite->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mSprite->Parent(this);

	Pos(pos);
	Rotation(rotation);

	mDistance = 650.0f;
	mSpeed = 500.0f;
	mGravity = 0.0f;

	mDamage = 10;
	mCanCrit = true;

	AddCollider(new BoxCollider(mSprite->ScaledDimensions()));

	mCollisionLayer = CollisionLayers::FriendlyProjectiles;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);

	if (first)
		CreateTrail();

	mTerraform = true;
	mInstantBreak = true;
}


Beam::~Beam()
{
}

void Beam::CreateTrail()
{
	int dist = 0;
	while (!PhysicsManager::Instance()->CheckCollision(this))
	{
		ProjectileManager::Instance()->AddProjectile(new Beam(mMap, Pos(), Rotation(), false));
		Translate(VEC2_RIGHT * mSprite->ScaledDimensions().x * 0.99f, local);

		dist += (Pos() - PrevPos()).Magnitude();

		if (HasLeftWall() || HasRightWall() || HasCeiling() || HasGround() || InsideTile())
			break;
		if (dist >= 450.0f)
			break;
	}
}
