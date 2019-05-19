#include "Flamethrower.h"

Flamethrower::Flamethrower(Map* map, Vector2 weaponOffset)
	: Weapon(map, weaponOffset)
{
	mSprite = new Texture("flamethrower.png");
	mSprite->Parent(this);
	Pos(mWeaponOffset);

	mBulletOffset.x = 20.0f;
	mBulletOffset.y = -3.0f;

	mKickBack = VEC2_ZERO;

	mRecoil = 15.0f;
	mRecoilAngle = 0.0f;

	mMaxAmmo = 9999;
	mAmmo = mMaxAmmo;
	mClipSize = 50;
	mClip = mClipSize;

	mFireDelay = 0.07f;
	mFireTimer = 0.0f;

	mReloadDelay = 1.0f;
	mReloadTimer = 0.0f;
}


Flamethrower::~Flamethrower()
{
}

bool Flamethrower::Fire()
{
	if (mClip > 0)
	{
		if (mReloadTimer <= 0.0f)
		{
			if (mFireTimer <= 0.0f)
			{
				//HandleRecoil(true);
				//Graphics::Instance()->CameraShake();

				ProjectileManager::Instance()->AddProjectile(new Flame(mMap, Pos() + RotateVector(mBulletOffset, Rotation()), Rotation()));
				mFireTimer = mFireDelay;
				mAudio->PlaySFX("flame.ogg", 0, 1);

				mClip--;
				if (mClip < 1)
				{
					Reload();
				}
			}

			return true;
		}
	}

	return false;
}