#include "Spell.h"

#include "PhysicsManager.h"

Spell::Spell()
{
	mTimer = Timer::Instance();

	mSprite = nullptr;

	mSpeed = VEC2_ZERO;
	mDistance = 0.0f;

	mCollisionLayer = CollisionLayers::BossAttack;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}

Spell::~Spell()
{
	delete mSprite;
}

void Spell::Hit(PhysEntity* other)
{
}

void Spell::Update()
{
	if (mDistance > 0.0f)
	{
		Vector2 prevPos = Pos();
		Pos(Pos() + (mSpeed * mTimer->DeltaTime()));

		mDistance -= (Pos() - prevPos).Magnitude();
		
		mSprite->Update();
	}
	else
		Active(false);
}

void Spell::Render()
{
	mSprite->Render();

	PhysEntity::Render();
}