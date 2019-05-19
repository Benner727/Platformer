#pragma once

#include "Projectile.h"

class Grenade : public Projectile
{
public:
	Grenade(Map* map, Vector2 pos, float rotation);
	~Grenade();

private:
	void Hit(PhysEntity* other) override;
};

