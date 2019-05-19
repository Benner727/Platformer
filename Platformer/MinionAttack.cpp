#include "MinionAttack.h"

#include "PhysicsManager.h"

MinionAttack::MinionAttack(Map* map, Vector2 pos, float rotation)
	: Projectile(map, pos, rotation)
{
	mSprite = new AnimatedTexture("link.png", 0, 0, 60, 14, 1, 0.0f, AnimatedTexture::ANIM_DIR::horizontal);
	mSprite->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mSprite->Scale(Vector2(0.75f, 1.0f));
	mSprite->Parent(this);

	mDistance = Graphics::SCREEN_WIDTH * 2.0f;
	mSpeed = 375.0f;

	mTerraform = true;
	mInstantBreak = true;

	AddCollider(new BoxCollider(Vector2(mSprite->ScaledDimensions().x * 0.75f, mSprite->ScaledDimensions().y * 0.35f)));

	mCollisionLayer = CollisionLayers::HostileProjectiles;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);

	Pos(pos);
	Rotation(rotation);
}

MinionAttack::~MinionAttack()
{
}