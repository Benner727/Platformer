#include "Player.h"

#include "PhysicsManager.h"

#include "Gun.h"
#include "Launcher.h"
#include "Flamethrower.h"
#include "Laser.h"

Player::Player(Map* map)
	: Actor(map)
{
	mInput = InputManager::Instance();
	mTimer = Timer::Instance();

	mSprite = new AnimatedTexture("player.png", 0, 0, 32, 64, 4, 1.0f, AnimatedTexture::ANIM_DIR::horizontal);
	mSprite->Parent(this);

	mWeapon.push_back(new Gun(map, Vector2(12.0f, 8.0f)));
	mWeapon.back()->Parent(this);

	mWeapon.push_back(new Launcher(map, Vector2(12.0f, 8.0f)));
	mWeapon.back()->Parent(this);

	mWeapon.push_back(new Flamethrower(map, Vector2(12.0f, 8.0f)));
	mWeapon.back()->Parent(this);

	mWeapon.push_back(new Laser(map, Vector2(12.0f, 8.0f)));
	mWeapon.back()->Parent(this);

	mWeaponSlot = 0;

	Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.33f));

	mMove = 0;

	mHorizontalSpeed = 0.0f;
	mVerticalSpeed = 0.0f;
	mGravity = -25.0f;
	mSpeed = 250.0f;

	mGunKick = VEC2_ZERO;

	mJump = false;
	mDoubleJump = true;

	mHealth = 1;
	mDead = false;

	mCameraLocked = false;

	//Initial setup
	mSprite->Flip(SDL_FLIP_HORIZONTAL);
	mWeapon[mWeaponSlot]->Rotation(178.0f);
	mWeapon[mWeaponSlot]->Flip();

	AddCollider(new BoxCollider(Vector2(15.0f, 56.0f)), Vector2(0.0f, 3.0f));

	mCollisionLayer = CollisionLayers::Friendly;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}

Player::~Player()
{
	delete mSprite;

	for (std::vector<Weapon*>::iterator it = mWeapon.begin(); it != mWeapon.end(); ++it)
		delete * it;
}

void Player::HandleMovement()
{
	mMove = 0;

	if (mInput->KeyDown(SDL_SCANCODE_A)) //Move Left
	{
		mMove--;
	}
	if (mInput->KeyDown(SDL_SCANCODE_D)) //Move Right
	{
		mMove++;
	}

	mHorizontalSpeed = (mMove * mSpeed + mGunKick.x) * mTimer->DeltaTime();
	mVerticalSpeed += (mGravity + mGunKick.y) * mTimer->DeltaTime();
	mGunKick = VEC2_ZERO;

	if (mVerticalSpeed < mGravity * 0.5f)
		mVerticalSpeed = mGravity * 0.5f;

	if (mInput->KeyPressed(SDL_SCANCODE_W)) //Jump
	{
		if (mJump)
		{
			mVerticalSpeed = mSpeed * 2.0f * mTimer->DeltaTime();
			mJump = false;
			mDoubleJump = true;
		}
		else if (mDoubleJump)
		{
			mVerticalSpeed = mSpeed * 2.0f * mTimer->DeltaTime();
			mJump = false;
			mDoubleJump = false;
		}
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_S)) //Fall
	{
		if (mVerticalSpeed > 0.0f)
			mVerticalSpeed = 0.0f;
	}
}

void Player::HandleCollision()
{
	Translate(VEC2_RIGHT * mHorizontalSpeed);
	if (HasLeftWall() || HasRightWall())
	{
		Pos(PrevPos());
		do
		{
			Translate(VEC2_RIGHT * sgn(mHorizontalSpeed));
			mHorizontalSpeed -= sgn(mHorizontalSpeed);
		} while (!HasLeftWall() && !HasRightWall());
		Pos(PrevPos());

		mHorizontalSpeed = 0.0f;
	}

	Translate(VEC2_UP * mVerticalSpeed);
	if (HasGround() || HasCeiling())
	{
		if (HasGround())
		{
			mJump = true;
			mDoubleJump = true;
		}

		Pos(PrevPos());
		do
		{
			Translate(VEC2_UP * sgn(mVerticalSpeed));
			mHorizontalSpeed -= sgn(mVerticalSpeed);
		} while (!HasGround() && !HasCeiling());
		Pos(PrevPos());

		mVerticalSpeed = 0.0f;
	}

	if (OutsideMap())
		mDead = true;
}

void Player::HandleWeapons()
{
	if (mInput->KeyPressed(SDL_SCANCODE_Q))
		--mWeaponSlot;
	else if (mInput->KeyPressed(SDL_SCANCODE_E))
		++mWeaponSlot;

	if (mWeaponSlot < 0)
		mWeaponSlot = mWeapon.size() - 1;
	else if (mWeaponSlot > mWeapon.size() - 1)
		mWeaponSlot = 0;
}

void Player::HandleGun()
{
	if (mInput->KeyDown(SDL_SCANCODE_R))
		mWeapon[mWeaponSlot]->Reload();

	Vector2 mousePos = mInput->MousePos() + Vector2(Graphics::Instance()->Camera()->x, Graphics::Instance()->Camera()->y);
	Vector2 direction = (mousePos - Pos(GameEntity::world)).Normalize();
	float angle = atan2(direction.y, direction.x) * RAD_TO_DEG;
	mWeapon[mWeaponSlot]->Aim(angle);

	if (mInput->MouseButtonDown(InputManager::MOUSE_BUTTON::left))
	{
		if (mWeapon[mWeaponSlot]->Fire())
		{
			mGunKick = mWeapon[mWeaponSlot]->KickBack();
			mGunKick = mGunKick * -direction;
		}
	}

	mWeapon[mWeaponSlot]->Update();
}

void Player::Hit(PhysEntity* other)
{
	mSprite->FlashRed();
	
	mHealth--;

	mDead = (mHealth <= 0);
}

void Player::Health(int health)
{
	mHealth = health;
}

int Player::Health() const
{
	return mHealth;
}

int Player::Ammo() const
{
	return mWeapon[mWeaponSlot]->Ammo();
}

int Player::Clip() const
{
	return mWeapon[mWeaponSlot]->Clip();
}

int Player::ClipSize() const
{
	return mWeapon[mWeaponSlot]->ClipSize();
}

bool Player::Dead() const
{
	return mDead;
}

void Player::Update()
{
	HandleMovement();
	HandleCollision();

	if (mInput->KeyPressed(SDL_SCANCODE_SPACE))
		mCameraLocked = !mCameraLocked;
		
	Graphics::Instance()->Camera(Pos(), mCameraLocked);

	if (mVerticalSpeed <= -3.0f || mVerticalSpeed >= 1.0f)
		mJump = false;

	if (mMove != 0)
		mSprite->Update();

	HandleWeapons();
	HandleGun();

	if (abs(mInput->MousePos().x + Graphics::Instance()->Camera()->x - Pos().x) > 12.0f)
	{
		if (mWeapon[mWeaponSlot]->Rotation() > 90.0f && mWeapon[mWeaponSlot]->Rotation() < 270.0f)
			mSprite->Flip(SDL_FLIP_HORIZONTAL);
		else
			mSprite->Flip(SDL_FLIP_NONE);

		mWeapon[mWeaponSlot]->Flip();
	}
}

void Player::Render()
{
	mSprite->Render();

	mWeapon[mWeaponSlot]->Render();

	PhysEntity::Render();
}