#include "Gun.h"

#include "Bullet.h"

Gun::Gun(Map* map, Vector2 weaponOffset)
	: Weapon(map, weaponOffset)
{
	mSprite = new Texture("gun.png");
	mSprite->Parent(this);
	Pos(mWeaponOffset);

	mBulletOffset.x = 8.0f;
	mBulletOffset.y = -3.0f;

	mKickBack = Vector2(5.0f, -2.0f);

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

Gun::~Gun()
{
}

bool Gun::Fire()
{
	if (mClip > 0)
	{
		if (mReloadTimer <= 0.0f)
		{
			if (mFireTimer <= 0.0f)
			{
				HandleRecoil(true);

				Graphics::Instance()->CameraShake();
				ProjectileManager::Instance()->AddProjectile(new Bullet(mMap, Pos() + RotateVector(mBulletOffset, Rotation()), Rotation()));

				mFireTimer = mFireDelay;
				mAudio->PlaySFX("cg1.wav", 0, 1);

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