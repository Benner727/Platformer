#pragma once

#include "Weapon.h"

class Launcher : public Weapon
{
public:
	Launcher(Map* map, Vector2 weaponOffset = VEC2_ZERO);
	~Launcher();

	bool Fire();
};