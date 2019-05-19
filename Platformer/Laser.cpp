#include "Laser.h"

#include "Beam.h"

Laser::Laser(Map* map, Vector2 weaponOffset)
	: Weapon(map, weaponOffset)
{
	mSprite = new Texture("laser.png");
	mSprite->Parent(this);
	Pos(mWeaponOffset);

	mBulletOffset.x = 8.0f;
	mBulletOffset.y = -3.0f;

	mKickBack = Vector2(0.0f, 0.0f);

	mRecoil = 0.0f;
	mRecoilAngle = 0.0f;

	mMaxAmmo = 9999;
	mAmmo = mMaxAmmo;
	mClipSize = 1;
	mClip = mClipSize;

	mFireDelay = 1.0f;
	mFireTimer = 0.0f;

	mReloadDelay = 2.0f;
	mReloadTimer = 0.0f;
}


Laser::~Laser()
{
}

bool Laser::Fire()
{
	if (mClip > 0)
	{
		if (mReloadTimer <= 0.0f)
		{
			if (mFireTimer <= 0.0f)
			{
				ProjectileManager::Instance()->AddProjectile(new Beam(mMap, Pos() + RotateVector(mBulletOffset, Rotation()), Rotation()));
				mFireTimer = mFireDelay;
				mAudio->PlaySFX("Rifleprimary2.ogg", 0, 1);

				mClip--;
				if (mClip < 1)
				{
					Reload();
				}

				return true;
			}
		}
	}

	return false;
}
