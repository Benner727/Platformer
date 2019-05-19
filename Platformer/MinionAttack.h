#ifndef MINIONATTACK_H
#define MINIONATTACK_H

#include "Projectile.h"

class MinionAttack : public Projectile
{
public:
	MinionAttack(Map* map, Vector2 pos, float rotation);
	~MinionAttack();
};

#endif