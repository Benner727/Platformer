#include "Bullet.h"

#include "PhysicsManager.h"

Bullet::Bullet(Map* map, Vector2 pos, float rotation)
	: Projectile(map, pos, rotation)
{
	mSprite = new AnimatedTexture("bullet.png", 0, 0, 8, 8, 2, (rand() % 2) ? 0.01 : 0.05f, AnimatedTexture::ANIM_DIR::horizontal);
	mSprite->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mSprite->Parent(this);

	Pos(pos);
	Rotation(rotation);

	mDistance = Graphics::SCREEN_WIDTH;
	mSpeed = 1000.0f;
	mGravity = 0.0f;

	mTerraform = true;

	mDamage = 15;
	mCanCrit = true;

	AddCollider(new CircleCollider(mSprite->ScaledDimensions().x * 0.5f));

	mCollisionLayer = CollisionLayers::FriendlyProjectiles;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}


Bullet::~Bullet()
{
}
