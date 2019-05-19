#include "TwinDragon.h"

#include "PhysicsManager.h"

TwinDragon::TwinDragon(Map* map, GameEntity* target)
	: Boss(map, target)
{
	mSprite = new AnimatedTexture("twindragon.png", 0, 0, 138, 84, 4, 0.65f, AnimatedTexture::ANIM_DIR::horizontal);
	mSprite->Parent(this);
	mSprite->Scale(Vector2(1.5f, 1.5f));

	mDeath = new AnimatedTexture("explosiondeath.png", 0, 0, 84, 87, 5, 1.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mDeath->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mDeath->Parent(this);
	mDeath->Scale(Vector2(1.5f, 1.5f));

	Pos(Vector2(Graphics::SCREEN_WIDTH * 1.45f, Graphics::SCREEN_HEIGHT * 0.2f));

	mHorizontalSpeed = -mSpeed * mTimer->DeltaTime();
	mVerticalSpeed = -mSpeed * mTimer->DeltaTime();
	mSpeed = 150.0f;

	mStepTimer = 0.0f;

	mFullHealth = 10000;
	mHealth = mFullHealth;

	mAttackDelay = 5.0f;
	mAttackTimer = mAttackDelay;

	mNextAttack = rand() % 2;

	mAttackWarning = true;

	mBossPhase = 0;
	mDiving = false;

	mTerraform = true;
	mInstantBreak = true;

	AddCollider(new CircleCollider(mSprite->ScaledDimensions().y * 0.35f));
}


TwinDragon::~TwinDragon()
{
	for (std::vector<Projectile*>::iterator it = mAttacks.begin(); it != mAttacks.end(); ++it)
		delete * it;
}

void TwinDragon::Hit(PhysEntity* other)
{
	switch (other->CollisionLayer())
	{
	case PhysEntity::CollisionLayers::FriendlyProjectiles:
		mSprite->FlashRed();

		mHealth -= other->Damage();

		if (mDiving && other->CanCrit())
			mHealth -= other->Damage();

		if (mHealth <= 0)
		{
			Active(false);
			mAudio->PlaySFX("explode.wav", 0, 3);
		}
		break;
	}
}

void TwinDragon::HandleMovement()
{
	if (!mDiving)
	{
		if (mTarget && mTarget->Pos().x < Pos().x - 100.0f)
			mHorizontalSpeed = -mSpeed * mTimer->DeltaTime();
		else if (mTarget && mTarget->Pos().x > Pos().x + 100.0f)
			mHorizontalSpeed = mSpeed * mTimer->DeltaTime();

		if (Pos().y < Graphics::SCREEN_HEIGHT * 0.2f)
			mVerticalSpeed = -mSpeed * mTimer->DeltaTime();
		else if (Pos().y > Graphics::SCREEN_HEIGHT * 0.3f)
			mVerticalSpeed = mSpeed * mTimer->DeltaTime();
	}
	else
	{
		mHorizontalSpeed = 0.0f;
		mVerticalSpeed = -mSpeed * mTimer->DeltaTime();

		if (Pos().y > Graphics::SCREEN_HEIGHT * 0.75f)
		{
			mSpeed /= 2.0f;
			mDiving = false;

			mAttackTimer = rand() % (int)mAttackDelay + 2.0f;
			mNextAttack = rand() % (2 + mBossPhase);
			mAttackWarning = true;
		}
	}

	Translate(VEC2_RIGHT * mHorizontalSpeed);
	Translate(VEC2_UP * mVerticalSpeed);
	HasGround();
}

void TwinDragon::HandlePhases()
{
	if (mHealth <= mFullHealth * 0.5f && mBossPhase == 0)
	{
		mAttackDelay = 3.0f;
		mBossPhase++;
	}
}

void TwinDragon::HandleAttack()
{
	if (mTarget)
	{
		if (mAttackTimer <= 0.0f)
		{
			Vector2 direction = (mTarget->Pos() - (Pos(GameEntity::world))).Normalize();
			float angle = atan2(direction.y, direction.x) * RAD_TO_DEG;

			mAttackTimer = rand() % (int)mAttackDelay + 1.0f;

			switch (mNextAttack)
			{
			case 0:
				mAttacks.push_back(new DragonBreath(mMap, Pos() + Vector2(mSprite->ScaledDimensions().x * 0.05f, mSprite->ScaledDimensions().y * 0.4f), angle * 0.95f));
				mAttacks.push_back(new DragonBreath(mMap, Pos() + Vector2(-mSprite->ScaledDimensions().x * 0.05f, mSprite->ScaledDimensions().y * 0.4f), angle * 1.05f));
				break;
			case 1:
				mAttacks.push_back(new DragonBreath(mMap, Pos() + Vector2(0.0f, mSprite->ScaledDimensions().y * 0.4f), angle));
				break;
			case 2:
				mDiving = true;
				mSpeed *= 2.0f;
				break;
			}

			if (!mDiving)
			{
				mNextAttack = rand() % (2 + mBossPhase);
				mAttackWarning = true;
			}
			else
			{
				mNextAttack = -1;
				mAttackWarning = false;
			}
		}
		else
			mAttackTimer -= mTimer->DeltaTime();

		if (mAttackTimer <= 0.5f && mAttackWarning)
		{
			mAttackWarning = false;

			switch (mNextAttack)
			{
			case 0:
			case 1:
				mAudio->PlaySFX("lava.ogg", 0, 2);
				break;
			case 2:
				mAudio->PlaySFX("Beast Growl.wav", 0, 2);
				break;
			}
		}
	}


}

void TwinDragon::Update()
{
	if (mHealth > 0)
	{
		HandleMovement();
		HandlePhases();
		HandleAttack();

		mSprite->Update();

		if (mStepTimer <= 0.0f)
		{
			mStepTimer = 0.9f;
			mAudio->PlaySFX("bird_flap.ogg", 0, 3);
		}
		else
			mStepTimer -= mTimer->DeltaTime();

		for (std::vector<Projectile*>::iterator it = mAttacks.begin(); it != mAttacks.end();)
		{
			if (!(*it)->Active())
			{
				delete * it;
				it = mAttacks.erase(it);
			}
			else
			{
				(*it)->Update();
				++it;
			}
		}
	}
	else
		mDeath->Update();
}

void TwinDragon::Render()
{
	if (mHealth > 0)
	{
		for (const auto& attack : mAttacks)
			attack->Render();

		mSprite->Render();
	}
	else if (mDeath->IsAnimating())
		mDeath->Render();

	PhysEntity::Render();
}
