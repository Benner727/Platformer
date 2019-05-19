#include "Minion.h"

#include "PhysicsManager.h"

Minion::Minion(Map* map, GameEntity* boss, GameEntity* player)
	: Actor(map), mBoss(boss), mPlayer(player)
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mSprite = new AnimatedTexture("minion.png", 0, 0, 111, 91, 3, 0.6f, AnimatedTexture::ANIM_DIR::horizontal);
	mSprite->Parent(this);
	
	mMap = map;

	mSpeed = 175.0f;
	mHorizontalSpeed = 0.0f;
	mVerticalSpeed = -mSpeed * mTimer->DeltaTime() * 0.1f;

	mDirection = true;

	mHealth = mFullHealth;

	mAttackDelay = 3;
	mAttackTimer = rand() % mAttackDelay + 1;

	mHealTimer = 1.0f;

	UpdateHealthBar();

	AddCollider(new BoxCollider(Vector2(mSprite->ScaledDimensions().x * 0.9f, mSprite->ScaledDimensions().y * 0.45f)), Vector2(3.0f, 18.0f));

	mCollisionLayer = CollisionLayers::Hostile;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}

Minion::~Minion()
{
	delete mSprite;

	for (std::vector<Texture*>::iterator it = mHealthBar.begin(); it != mHealthBar.end(); ++it)
		delete * it;
}

void Minion::Hit(PhysEntity* other)
{
	mSprite->FlashRed();

	mHealth -= other->Damage();

	mHealTimer = 1.0f;

	UpdateHealthBar();
}

void Minion::HandleMovement()
{
	if (mBoss && (Pos() - mBoss->Pos()).Magnitude() < 250.0f)
		mDirection = true;
	else if (mBoss && (Pos() - mBoss->Pos()).Magnitude() > 700.0f)
		mDirection = false;
	mDirection ? mHorizontalSpeed = mSpeed * mTimer->DeltaTime() : mHorizontalSpeed = -mSpeed * mTimer->DeltaTime();

	if (Pos().y > Graphics::SCREEN_HEIGHT * 0.8f)
		mVerticalSpeed = mSpeed * mTimer->DeltaTime() * 0.1f;
	else if (Pos().y < Graphics::SCREEN_HEIGHT * 0.1f)
		mVerticalSpeed = -mSpeed * mTimer->DeltaTime() * 0.1f;

	Translate(VEC2_RIGHT * mHorizontalSpeed);
	if (HasLeftWall())
	{
		do
		{
			Translate(VEC2_RIGHT);
		} while (HasLeftWall());

		mHorizontalSpeed = 0.0f;

		mDirection = !mDirection;
	}
	else if (HasRightWall())
	{
		do
		{
			Translate(-VEC2_RIGHT);
		} while (HasRightWall());

		mHorizontalSpeed = 0.0f;

		mDirection = !mDirection;
	}

	Translate(VEC2_UP * mVerticalSpeed);

	if (mVerticalSpeed < 0 && HasGround())
	{
		do
		{
			Translate(VEC2_UP);
		} while (HasGround());

		mVerticalSpeed *= -1.0f;
	}
	else if (mVerticalSpeed > 0 && HasCeiling())
	{
		do
		{
			Translate(-VEC2_UP);
		} while (HasCeiling());

		mVerticalSpeed *= -1.0f;
	}
}

void Minion::HandleAttack()
{
	if (mPlayer)
	{
		if (mAttackTimer <= 0.0f)
		{
			Vector2 direction = (mPlayer->Pos() - (Pos(GameEntity::world))).Normalize();
			float angle = atan2(direction.y, direction.x) * RAD_TO_DEG;

			mAudio->PlaySFX("electric.ogg", 0, 2);
			ProjectileManager::Instance()->AddProjectile(new MinionAttack(mMap, Pos(), angle));
			mAttackTimer = rand() % mAttackDelay + 1;
		}
		else
			mAttackTimer -= mTimer->DeltaTime();
	}
}

void Minion::UpdateHealthBar()
{
	for (std::vector<Texture*>::iterator it = mHealthBar.begin(); it != mHealthBar.end(); ++it)
		delete * it;
	mHealthBar.clear();

	int newSize = 15.0f * ((float)mHealth / mFullHealth);
	float y = Pos().y - 50.0f;

	for (int i = 0; i < 15; i++)
	{
		if (i < newSize)
		{
			mHealthBar.push_back(new Texture("minihealthbar.png", 0, 0, 2, 2));
			mHealthBar.back()->Pos(Vector2(Pos().x + 2.0f * i, y));
			mHealthBar.back()->Parent(this);
		}
		else
		{
			mHealthBar.push_back(new Texture("minihealthbar.png", 2, 0, 2, 2));
			mHealthBar.back()->Pos(Vector2(Pos().x + 2.0f * i, y));
			mHealthBar.back()->Parent(this);
		}
	}
}

bool Minion::Dead() const
{
	return (mHealth <= 0.0f);
}

void Minion::Update()
{
	HandleMovement();
	HandleAttack();

	mDirection ? mSprite->Flip(SDL_RendererFlip::SDL_FLIP_HORIZONTAL) : mSprite->Flip(SDL_RendererFlip::SDL_FLIP_NONE);
	mSprite->Update();

	mHealTimer -= mTimer->DeltaTime();
	if (mHealTimer <= 0.0f)
	{
		mHealTimer = 1.0f;

		if (mHealth < mFullHealth)
		{
			mHealth += mFullHealth * 0.01f;
			UpdateHealthBar();
		}
		else
			mHealth = mFullHealth;
	}
}

void Minion::Render()
{
	mSprite->Render();

	for (const auto& health : mHealthBar)
		health->Render();

	PhysEntity::Render();
}
