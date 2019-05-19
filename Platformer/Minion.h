#ifndef MINION_H
#define MINION_H

#include "AudioManager.h"
#include "MinionAttack.h"
#include "ProjectileManager.h"

class Minion : public Actor
{
public:
	Minion(Map* map, GameEntity* boss = nullptr, GameEntity* player = nullptr);
	~Minion();

private:
	Timer* mTimer;
	AudioManager* mAudio;

	Map* mMap;

	AnimatedTexture* mSprite;

	float mHorizontalSpeed;
	float mVerticalSpeed;
	float mSpeed;

	bool mDirection;

	const int mFullHealth = 3000;

	std::vector<Texture*> mHealthBar;

	GameEntity* mBoss;
	GameEntity* mPlayer;

	int mAttackDelay;
	float mAttackTimer;

	float mHealTimer;

	void Hit(PhysEntity* other) override;

	void UpdateHealthBar();

	void HandleMovement();
	void HandleAttack();

public:
	bool Dead() const;

	void Update();
	void Render();
};

#endif