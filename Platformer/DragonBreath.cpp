#include "DragonBreath.h"

#include "PhysicsManager.h"

DragonBreath::DragonBreath(Map* map, Vector2 pos, float rotation)
	: Projectile(map, pos, rotation)
{
	mSprite = new AnimatedTexture("dragonbreath.png", 0, 0, 27, 12, 4, 0.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mSprite->Parent(this);

	mDistance = Graphics::SCREEN_WIDTH * 2.0f;
	mSpeed = 250.0f;

	mTerraform = true;
	mInstantBreak = true;

	AddCollider(new CircleCollider(mSprite->ScaledDimensions().y * 0.45f), Vector2(5.0f, 0.0f));

	mCollisionLayer = CollisionLayers::HostileProjectiles;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);

	Pos(pos);
	Rotation(rotation);
}


DragonBreath::~DragonBreath()
{
}
