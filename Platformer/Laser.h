#pragma once

#include "Weapon.h"

class Laser : public Weapon
{
public:
	Laser(Map* map, Vector2 weaponOffset = VEC2_ZERO);
	~Laser();

	bool Fire();
};

