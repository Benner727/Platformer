#include "Projectile.h"

Projectile::Projectile(Map* map, Vector2 pos, float rotation)
	: Actor(map)
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mHorizontalSpeed = 0.0f;
	mVerticalSpeed = 0.0f;

	mSpeed = 1000.0f;
	mDistance = 1000.0f;
	mGravity = 0.0f;

	mSprite = nullptr;
}

Projectile::~Projectile()
{
	delete mSprite;
}

void Projectile::Hit(PhysEntity* other)
{
	Active(false);
}

bool Projectile::CleanUp()
{
	return !(Active());
}

void Projectile::Update()
{
	if (Active())
	{
		mSprite->Update();

		if (mDistance > 0.0f)
		{
			mHorizontalSpeed = mSpeed * mTimer->DeltaTime();
			mVerticalSpeed -= mGravity * mTimer->DeltaTime();

			Translate(VEC2_RIGHT * mHorizontalSpeed, local);
			Translate(VEC2_UP * mVerticalSpeed);

			mDistance -= mHorizontalSpeed;

			if (HasLeftWall() || HasRightWall() || HasCeiling() || HasGround() || InsideTile())
			{
				//Active(false);
				Hit(nullptr);
			}
		}
		else
			Active(false);
	}
}

void Projectile::Render()
{
	if (Active())
		mSprite->Render();

	PhysEntity::Render();
}