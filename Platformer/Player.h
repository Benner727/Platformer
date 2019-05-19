#ifndef PLAYER_H
#define PLAYER_H

#include "Weapon.h"
#include "InputManager.h"

class Player : public Actor
{
public:
	Player(Map* map);
	~Player();

	InputManager* mInput;
	Timer* mTimer;

	AnimatedTexture* mSprite;

	std::vector<Weapon*> mWeapon;
	int mWeaponSlot;

private:
	int mMove;

	float mHorizontalSpeed;
	float mVerticalSpeed;
	float mGravity;
	float mSpeed;

	Vector2 mGunKick;

	bool mOneWayPlatform;
	bool mJump;
	bool mDoubleJump;

	bool mDead;

	bool mCameraLocked;

	void HandleMovement();
	void HandleCollision();
	void HandleWeapons();
	void HandleGun();

	void Hit(PhysEntity* other) override;

public:
	void Health(int health);
	int Health() const;

	int Ammo() const;
	int Clip() const;
	int ClipSize() const;

	bool Dead() const;

	void Update();
	void Render();
};

#endif