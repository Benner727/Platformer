#ifndef DEMON_H
#define DEMON_H

#include "Boss.h"
#include "Minion.h"
#include "Spell.h"

class Demon : public Boss
{
public:
	Demon(Map* map, GameEntity* target = nullptr);
	~Demon();

private:
	AnimatedTexture* mIdle;

	std::vector<Spell*> mSpells;
	std::vector<Minion*> mMinions;

	int mAttackPhase;
	float mPhaseTimer;

	float mHealTimer;

	void Hit(PhysEntity* other) override;

	void HandleMovement();
	void HandlePhases();

	void RainFire();
	void ThrowSpikes();
	void HandleAttack();

	void HandleMinions();

public:
	void Update();
	void Render();
};

#endif