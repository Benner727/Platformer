#ifndef BOSS_H
#define BOSS_H

#include "AnimatedTexture.h"
#include "Actor.h"
#include "AudioManager.h"

class Boss : public Actor
{
public:
	Boss(Map* map, GameEntity* target = nullptr);
	~Boss();

protected:
	Timer* mTimer;
	AudioManager* mAudio;

	Map* mMap;

	AnimatedTexture* mSprite;
	AnimatedTexture* mDeath;

	float mHorizontalSpeed;
	float mVerticalSpeed;
	float mGravity;
	float mSpeed;

	float mStepTimer;

	int mFullHealth;

	GameEntity* mTarget;
	float mAttackDelay;
	float mAttackTimer;
	
	int mNextAttack;
	bool mAttackWarning;

	int mBossPhase;

	void Hit(PhysEntity* other) override;

public:
	int FullHealth() const;
	int Health() const;
	bool Dead() const;

	void Update();
	void Render();
};

#endif