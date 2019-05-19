#pragma once

#include "Weapon.h"
#include "Flame.h"

class Flamethrower : public Weapon
{
public:
	Flamethrower(Map* map, Vector2 weaponOffset = VEC2_ZERO);
	~Flamethrower();

	bool Fire();
};

