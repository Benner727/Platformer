#ifndef WEAPON_H
#define WEAPON_H

#include "ProjectileManager.h"

class Weapon : public GameEntity
{
public:
	Weapon(Map* map, Vector2 weaponOffset = VEC2_ZERO);
	~Weapon();

private:
	Timer* mTimer;

protected:
	AudioManager* mAudio;

	Texture* mSprite;

	Map* mMap;

	Vector2 mWeaponOffset;
	Vector2 mBulletOffset;

	int mMaxAmmo;
	int mAmmo;
	float mClipSize;
	float mClip;

	Vector2 mKickBack;

	float mRecoil;
	float mRecoilAngle;

	float mFireDelay;
	float mFireTimer;

	float mReloadDelay;
	float mReloadTimer;

	void HandleRecoil(bool shooting);

public:
	int Ammo() const;
	int Clip() const;
	int ClipSize() const;

	Vector2 KickBack() const;

	void Reload();
	virtual bool Fire() = 0;

	void Aim(float angle);

	void Flip();

	void Update();
	void Render();
};

#endif