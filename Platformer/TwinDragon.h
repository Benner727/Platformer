#ifndef TWINDRAGON_H
#define TWINDRAGON_H

#include "Boss.h"
#include "DragonBreath.h"

class TwinDragon  : public Boss
{
public:
	TwinDragon(Map* map, GameEntity* target = nullptr);
	~TwinDragon();

private:
	std::vector<Projectile*> mAttacks;

	bool mDiving;

	void Hit(PhysEntity* other) override;

	void HandleMovement();
	void HandlePhases();
	void HandleAttack();

public:
	void Update();
	void Render();
};

#endif