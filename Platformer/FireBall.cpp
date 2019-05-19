#include "FireBall.h"

FireBall::FireBall()
{
	mSprite = new AnimatedTexture("fireball.png", 0, 0, 34, 70, 6, 1.0f, AnimatedTexture::ANIM_DIR::horizontal);
	mSprite->Parent(this);
	mSprite->Rotate(-45.0f);

	mSpeed = { 250.0f, 300.0f };
	mDistance = Graphics::SCREEN_WIDTH * 2.0f;

	AddCollider(new CircleCollider(mSprite->ScaledDimensions().x * 0.3f), Vector2(13.0f, 14.0f));
}

FireBall::~FireBall()
{
}

void FireBall::Hit(PhysEntity* other)
{
	Active(false);
}
