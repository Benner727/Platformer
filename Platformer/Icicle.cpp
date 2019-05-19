#include "Icicle.h"

Icicle::Icicle()
{
	mSprite = new AnimatedTexture("icicle.png", 0, 0, 63, 13, 6, 1.0f, AnimatedTexture::ANIM_DIR::horizontal);
	mSprite->Parent(this);

	mSpeed = { 375.0f + rand() % 25, 0.0f };
	mDistance = Graphics::SCREEN_WIDTH * 3.0f;

	AddCollider(new BoxCollider(mSprite->ScaledDimensions() * 0.45f), Vector2(12.0f, 0.0f));
}

Icicle::~Icicle()
{
}

void Icicle::Hit(PhysEntity* other)
{
	Active(false);
}
