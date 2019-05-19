#include "Launcher.h"

#include "Grenade.h"

Launcher::Launcher(Map* map, Vector2 weaponOffset)
	: Weapon(map, weaponOffset)
{
	mSprite = new Texture("launcher.png");
	mSprite->Parent(this);
	Pos(mWeaponOffset);

	mBulletOffset.x = 8.0f;
	mBulletOffset.y = -3.0f;

	mKickBack = Vector2(15.0f, -5.0f);

	mRecoil = 90.0f;
	mRecoilAngle = 0.0f;

	mMaxAmmo = 9999;
	mAmmo = mMaxAmmo;
	mClipSize = 3;
	mClip = mClipSize;

	mFireDelay = 1.0f;
	mFireTimer = 0.0f;

	mReloadDelay = 2.0f;
	mReloadTimer = 0.0f;
}

Launcher::~Launcher()
{
}

bool Launcher::Fire()
{
	if (mClip > 0)
	{
		if (mReloadTimer <= 0.0f)
		{
			if (mFireTimer <= 0.0f)
			{
				HandleRecoil(true);

				Graphics::Instance()->CameraShake();
				ProjectileManager::Instance()->AddProjectile(new Grenade(mMap, Pos() + RotateVector(mBulletOffset, Rotation()), Rotation()));
				mFireTimer = mFireDelay;
				mAudio->PlaySFX("cg1.wav", 0, 1);

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