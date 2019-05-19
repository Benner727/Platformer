#include "Grenade.h"

#include "PhysicsManager.h"
#include "EventManager.h"
#include "Explosion.h"

Grenade::Grenade(Map* map, Vector2 pos, float rotation)
	: Projectile(map, pos, rotation)
{
	mSprite = new AnimatedTexture("grenade.png", 0, 0, 8, 8, 2, 0.05f, AnimatedTexture::ANIM_DIR::horizontal);
	mSprite->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mSprite->Parent(this);

	Pos(pos);
	Rotation(rotation);

	mDistance = Graphics::SCREEN_WIDTH;
	mSpeed = 750.0f;
	mGravity = 10.0f;

	mTerraform = true;

	mDamage = 10;
	mCanCrit = true;

	AddCollider(new CircleCollider(mSprite->ScaledDimensions().x * 0.5f));

	mCollisionLayer = CollisionLayers::FriendlyProjectiles;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}

Grenade::~Grenade()
{
}

void Grenade::Hit(PhysEntity * other)
{
	Active(false);

	if (mDistance <= Graphics::SCREEN_WIDTH * 0.9f)
	{
		EventManager::Instance()->AddEvent(new Explosion(mMap, Pos()));
	}
}
