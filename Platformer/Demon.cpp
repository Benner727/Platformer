#include "Demon.h"

#include "FireBall.h"
#include "Icicle.h"

#include "PhysicsManager.h"

Demon::Demon(Map* map, GameEntity* target)
	: Boss(map, target)
{
	mSprite = new AnimatedTexture("boss.png", 0, 0, 96, 123, 4, 1.2f, AnimatedTexture::ANIM_DIR::horizontal);
	mSprite->Parent(this);
	mSprite->Scale(Vector2(3.0f, 3.0f));

	mIdle = new AnimatedTexture("bossidle.png", 0, 0, 96, 123, 4, 1.2f, AnimatedTexture::ANIM_DIR::horizontal);
	mIdle->Parent(this);
	mIdle->Scale(Vector2(3.0f, 3.0f));

	mDeath = new AnimatedTexture("bossdeath.png", 0, 0, 96, 123, 4, 1.5f, AnimatedTexture::ANIM_DIR::horizontal);
	mDeath->WrapMode(AnimatedTexture::WRAP_MODE::once);
	mDeath->Parent(this);
	mDeath->Scale(Vector2(3.0f, 3.0f));

	Pos(Vector2(Graphics::SCREEN_WIDTH * 0.15f, Graphics::SCREEN_HEIGHT * 0.45f));

	mHorizontalSpeed = 0.0f;
	mVerticalSpeed = 0.0f;
	mGravity = 50.0f;
	mSpeed = 100.0f;

	mStepTimer = 0.0f;

	mFullHealth = 50000;
	mHealth = mFullHealth;

	mAttackDelay = 5.0f;
	mAttackTimer = mAttackDelay + rand() % (int)mAttackDelay;

	mNextAttack = rand() % 2;
	mAttackPhase = 0;
	mPhaseTimer = 0.0f;

	mAttackWarning = true;

	mBossPhase = 0;
	mHealTimer = 1.0f;

	mTerraform = true;
	mInstantBreak = true;

	AddCollider(new BoxCollider(Vector2(mSprite->ScaledDimensions().x * 0.75f, mSprite->ScaledDimensions().y)), Vector2(10.0f, 0.0f));
}

Demon::~Demon()
{
	delete mIdle;

	for (std::vector<Spell*>::iterator it = mSpells.begin(); it != mSpells.end(); ++it)
		delete * it;

	for (std::vector<Minion*>::iterator it = mMinions.begin(); it != mMinions.end(); ++it)
		delete * it;
}

void Demon::Hit(PhysEntity* other)
{
	if (mMinions.empty() && mHealth > 0)
	{
		switch (other->CollisionLayer())
		{
		case PhysEntity::CollisionLayers::FriendlyProjectiles:
			mSprite->FlashRed();

			mHealth -= other->Damage();

			//Calculate headshot damage
			if (other->CanCrit() && (other->Pos().y < 234.0f && other->Pos().y > 116.0f))
				mHealth -= other->Damage();

			if (mHealth <= 0)
			{
				Active(false);
				mAudio->PlaySFX("teleport.wav", 0, 3);
			}
			break;
		}
	}

	//std::cout << mHealth << std::endl;
}

void Demon::HandleMovement()
{
	mHorizontalSpeed = mSpeed * mTimer->DeltaTime();
	mVerticalSpeed -= mGravity * mTimer->DeltaTime();

	Translate(VEC2_RIGHT * mHorizontalSpeed);
	if (HasLeftWall())
	{
		do
		{
			Translate(VEC2_RIGHT);
		} while (HasLeftWall());

		mHorizontalSpeed = 0.0f;
	}
	else if (HasRightWall())
	{
		do
		{
			Translate(-VEC2_RIGHT);
		} while (HasRightWall());

		mHorizontalSpeed = 0.0f;
	}

	Translate(VEC2_UP * mVerticalSpeed);
	if (HasGround())
	{
		do
		{
			Translate(VEC2_UP);
		} while (HasGround());

		mVerticalSpeed = 0.0f;
	}
	else if (HasCeiling())
	{
		do
		{
			Translate(-VEC2_UP);
		} while (HasCeiling());

		mVerticalSpeed = 0.0f;
	}
}

void Demon::HandlePhases()
{
	if (mBossPhase == 0 && mHealth <= mFullHealth * 0.75f)
	{
		mMinions.push_back(new Minion(mMap, this, mTarget));
		mMinions.back()->Pos(Vector2(Pos().x + (mSprite->ScaledDimensions().x * 0.75f), Graphics::SCREEN_HEIGHT * 0.15f));

		mIdle->ResetAnimation();

		mBossPhase++;
		mHealTimer = 1.0f;

		mAudio->PlaySFX("Beast Growl.wav", 0, 3);
	}
	else if (mBossPhase == 1 && mHealth <= mFullHealth * 0.5f)
	{
		for (int i = 0; i < 2; i++)
		{
			mMinions.push_back(new Minion(mMap, this, mTarget));
			mMinions.back()->Pos(Vector2(Pos().x + (mSprite->ScaledDimensions().x * 0.75f) + (i * 200.0f), Graphics::SCREEN_HEIGHT * 0.15f));
		}
		mIdle->ResetAnimation();

		mSpeed *= 2.0f;

		mBossPhase++;
		mHealTimer = 1.0f;

		mAudio->PlaySFX("Beast Growl.wav", 0, 3);
	}
	else if (mBossPhase == 2 && mHealth <= mFullHealth * 0.25f)
	{
		for (int i = 0; i < 3; i++)
		{
			mMinions.push_back(new Minion(mMap, this, mTarget));
			mMinions.back()->Pos(Vector2(Pos().x + (mSprite->ScaledDimensions().x * 0.75f) + (i * 150.0f), Graphics::SCREEN_HEIGHT * 0.15f));
		}
		mIdle->ResetAnimation();

		mAttackDelay = 3.0f;

		mBossPhase++;
		mHealTimer = 1.0f;

		mAudio->PlaySFX("Beast Growl.wav", 0, 3);
	}
}

void Demon::RainFire()
{
	switch (mAttackPhase)
	{
	case 0:
		for (int i = 0; i < 15; i++)
		{
			mSpells.push_back(new FireBall());

			Vector2 newPos = Vector2(Pos().x, Pos().y);
			newPos.y = 0.0f - (rand() % 100);
			newPos.x += (i * 96.0f);

			mSpells.back()->Pos(newPos);
		}
		mAttackPhase++;
		mPhaseTimer = 0.5f;
		break;
	case 1:
		for (int i = 0; i < 15; i++)
		{
			mSpells.push_back(new FireBall());

			Vector2 newPos = Vector2(Pos().x, Pos().y);
			newPos.y = 0.0f - (rand() % 100);
			newPos.x += (i * 96.0f);

			mSpells.back()->Pos(newPos);
		}
		mAttackPhase = 0;
		mPhaseTimer = 0.0f;
		mAttackTimer = mAttackDelay;
		mNextAttack = rand() % 2;
		mAttackWarning = true;
		break;
	}
}

void Demon::ThrowSpikes()
{
	switch (mAttackPhase)
	{
	case 0:
		for (int i = 0; i < 3; i++)
		{
			mSpells.push_back(new Icicle());
			Vector2 newPos = Vector2(Pos().x - (rand() % (int)mSprite->ScaledDimensions().x), 130.0f);
			newPos.y += i * 128.0f;
			mSpells.back()->Pos(newPos);
		}
		mAttackPhase++;
		mPhaseTimer = 1.0f;
		mAttackWarning = true;
		break;
	case 1:
		for (int i = 0; i < 4; i++)
		{
			mSpells.push_back(new Icicle());
			Vector2 newPos = Vector2(Pos().x - (rand() % (int)mSprite->ScaledDimensions().x), 80.0f);
			newPos.y += i * 96.0f;
			mSpells.back()->Pos(newPos);
		}
		mAttackPhase++;
		mPhaseTimer = 1.5f;
		mAttackWarning = true;
		break;
	case 2:
		for (int i = 0; i < 5; i++)
		{
			mSpells.push_back(new Icicle());
			Vector2 newPos = Vector2(Pos().x - (rand() % (int)mSprite->ScaledDimensions().x), 15.0f);
			newPos.y += i * 96.0f;
			mSpells.back()->Pos(newPos);
		}
		mAttackPhase = 0;
		mPhaseTimer = 0.0f;
		mAttackTimer = mAttackDelay;
		mNextAttack = rand() % 2;
		mAttackWarning = true;
		break;
	}
}

void Demon::HandleAttack()
{
	if (mAttackTimer <= 0.0f)
	{
		if (mPhaseTimer <= 0.0f)
		{
			if (mTarget && (Pos() - mTarget->Pos()).Magnitude() <= Graphics::SCREEN_WIDTH * 2.0f)
			{
				switch (mNextAttack)
				{
				case 0:
					ThrowSpikes();
					break;
				case 1:
					RainFire();
					break;
				default:
					mNextAttack = rand() % 2;
				}
			}
		}
		else
			mPhaseTimer -= mTimer->DeltaTime();
	}
	else
		mAttackTimer -= mTimer->DeltaTime();

	if (mAttackTimer <= 1.0f && mPhaseTimer <= 1.0f)
	{
		if (mTarget && (Pos() - mTarget->Pos()).Magnitude() <= Graphics::SCREEN_WIDTH * 2.0f && mAttackWarning)
		{
			mAttackWarning = false;
			switch (mNextAttack)
			{
			case 0:
				mAudio->PlaySFX("icespell.wav", 0, 2);
				break;
			case 1:
				mAudio->PlaySFX("firespell.ogg", 0, 2);
				break;
			}
		}
	}
}

void Demon::HandleMinions()
{
	for (std::vector<Minion*>::iterator it = mMinions.begin(); it != mMinions.end();)
	{
		if ((*it)->Dead())
		{
			delete * it;
			it = mMinions.erase(it);
		}
		else
		{
			(*it)->Update();
			++it;
		}
	}

	if (mMinions.size())
	{
		mHealTimer -= mTimer->DeltaTime();

		if (mHealTimer <= 0.0f)
		{
			mHealTimer = 1.0f;

			if (mHealth < mFullHealth)
				mHealth += (mFullHealth * 0.002f) * mMinions.size();
			else
				mHealth = mFullHealth;
		}
	}
	else
	{
		mAttackPhase = 0;
		mPhaseTimer = 0.0f;
		mAttackTimer = mAttackDelay;
		mNextAttack = rand() % 2;
		mAttackWarning = true;
	}
}

void Demon::Update()
{
	if (mHealth > 0)
	{
		if (mMinions.empty())
		{
			HandleMovement();
			HandlePhases();
			HandleAttack();

			mSprite->Update();

			if (mStepTimer <= 0.0f)
			{
				mStepTimer = 0.6f;
				mAudio->PlaySFX("stomp.ogg", 0, 3);
			}
			else
				mStepTimer -= mTimer->DeltaTime();
		}
		else
		{
			HandleMinions();

			mIdle->Update();
		}

		for (std::vector<Spell*>::iterator it = mSpells.begin(); it != mSpells.end();)
		{
			if (!(*it)->Active())
			{
				delete * it;
				it = mSpells.erase(it);
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

void Demon::Render()
{
	if (mHealth > 0)
	{
		if (mMinions.empty())
			mSprite->Render();
		else
			mIdle->Render();

		for (const auto& spell : mSpells)
			spell->Render();

		for (const auto& minion : mMinions)
			minion->Render();
	}
	else if (mDeath->IsAnimating())
		mDeath->Render();

	PhysEntity::Render();
}