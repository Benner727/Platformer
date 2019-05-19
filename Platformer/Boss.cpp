#include "Boss.h"

#include "PhysicsManager.h"

Boss::Boss(Map* map, GameEntity* target)
	: Actor(map), mTarget(target)
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mMap = map;

	mSprite = nullptr;

	mHorizontalSpeed = 0.0f;
	mVerticalSpeed = 0.0f;
	mGravity = 50.0f;
	mSpeed = 100.0f;

	mStepTimer = 0.0f;

	mFullHealth = 1000;
	mHealth = mFullHealth;

	mAttackDelay = 1.0f;
	mAttackTimer = mAttackDelay + rand();

	mNextAttack = 0;

	mAttackWarning = true;

	mTerraform = true;
	mInstantBreak = true;

	mCollisionLayer = CollisionLayers::Boss;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}

Boss::~Boss()
{
	delete mSprite;

	delete mDeath;
}

void Boss::Hit(PhysEntity* other)
{
	
}

int Boss::FullHealth() const
{
	return mFullHealth;
}

int Boss::Health() const
{
	return mHealth;
}

bool Boss::Dead() const
{
	return ((mHealth <= 0) && !mDeath->IsAnimating());
}

void Boss::Update()
{
}

void Boss::Render()
{
}