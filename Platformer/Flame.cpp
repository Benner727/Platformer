#include "Flame.h"

#include "PhysicsManager.h"

Flame::Flame(Map* map, Vector2 pos, float rotation)
	: Projectile(map, pos, rotation)
{
	mSprite = new AnimatedTexture("flame.png", 0, 0, 13, 10, 2, 0.1f, AnimatedTexture::ANIM_DIR::horizontal);
	mSprite->Scale(Vector2(1.5f, 1.5f));
	mSprite->Parent(this);

	Pos(pos);

	static int flame = 0;
	switch (flame)
	{
	case 0:
		Rotation(rotation + 5.0f);
		Translate(VEC2_UP * 5.0f);
		break;
	case 1:
		Rotation(rotation + 0.0f);
		//Translate(VEC2_UP * 5.0f);
		break;
	case 2:
		Rotation(rotation - 5.0f);
		Translate(VEC2_UP * -5.0f);
		break;
	}
	
	(flame < 2) ? flame++ : flame = 0;

	mDistance = 200.0f;
	mSpeed = 300.0f;
	mGravity = 0.0f;

	mDamage = 25;

	AddCollider(new CircleCollider(mSprite->ScaledDimensions().x * 0.4f));

	mCollisionLayer = CollisionLayers::FriendlyProjectiles;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}


Flame::~Flame()
{
}
