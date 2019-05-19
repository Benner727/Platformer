#include "Weapon.h"

Weapon::Weapon(Map* map, Vector2 weaponOffset)
	: mMap(map), mWeaponOffset(weaponOffset)
{
	mTimer = Timer::Instance();

	mAudio = AudioManager::Instance();

	mSprite = nullptr;

	mBulletOffset = VEC2_ZERO;

	mRecoil = 15.0f;
	mRecoilAngle = 0.0f;

	mMaxAmmo = 9999;
	mAmmo = mMaxAmmo;
	mClipSize = 45;
	mClip = mClipSize;

	mKickBack = VEC2_ZERO;

	mFireDelay = 0.0f;
	mFireTimer = 0.0f;

	mReloadDelay = 1.0f;
	mReloadTimer = 0.0f;
}

Weapon::~Weapon()
{
	delete mSprite;
}

void Weapon::HandleRecoil(bool shooting)
{
	if (shooting)
	{
		if (mRecoilAngle < mRecoil)
			mRecoilAngle += mRecoil * mTimer->DeltaTime();
		else
			mRecoilAngle = mRecoil;
	}
	else
	{
		if (mRecoilAngle > 0.0f)
			mRecoilAngle -= (mRecoil * 2.0f) * mTimer->DeltaTime();
		else
			mRecoilAngle = 0.0f;
	}
}


int Weapon::Ammo() const
{
	return mAmmo;
}

int Weapon::Clip() const
{
	return mReloadTimer > 0.0f ? 0 : mClip;
}

int Weapon::ClipSize() const
{
	return mClipSize;
}

Vector2 Weapon::KickBack() const
{
	return mKickBack;
}

void Weapon::Reload()
{
	if (mAmmo > 0)
	{
		if (mClip != mClipSize)
		{
			mRecoilAngle = 0.0f;

			mReloadTimer = mReloadDelay;

			int reloadAmount = mClipSize - mClip;

			if (reloadAmount <= mAmmo)
			{
				mAmmo -= reloadAmount;
				mClip = mClipSize;
			}
			else
			{
				mClip = mAmmo;
				mAmmo = 0;
			}

			if (mReloadTimer > 0.0f)
				mAudio->PlaySFX("reload.ogg", 0, 5);
		}
	}
}

void Weapon::Aim(float angle)
{
	Rotation(angle);

	if (Rotation() > 90.0f && Rotation() < 270.0f)
	{
		Rotate(mRecoilAngle);
	}
	else
	{
		Rotate(-mRecoilAngle);
	}
}

void Weapon::Flip()
{
	if (Rotation() > 90.0f && Rotation() < 270.0f)
	{
		if (mWeaponOffset.x > 0) mWeaponOffset.x *= -1;
		if (mBulletOffset.y < 0) mBulletOffset.y *= -1;
		mSprite->Flip(SDL_FLIP_VERTICAL);
		Pos(mWeaponOffset);
	}
	else
	{
		if (mWeaponOffset.x < 0) mWeaponOffset.x *= -1;
		if (mBulletOffset.y > 0) mBulletOffset.y *= -1;
		mSprite->Flip(SDL_FLIP_NONE);
		Pos(mWeaponOffset);
	}
}

void Weapon::Update()
{
	if (mFireTimer > 0.0f)
		mFireTimer -= mTimer->DeltaTime();
	else
		HandleRecoil(false);

	if (mReloadTimer > 0.0f)
		mReloadTimer -= mTimer->DeltaTime();

	//Flip();
}

void Weapon::Render()
{
	mSprite->Render();
}