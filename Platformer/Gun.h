#ifndef GUN_H
#define GUN_H

#include "Weapon.h"

class Gun : public Weapon
{
public:
	Gun(Map* map, Vector2 weaponOffset = VEC2_ZERO);
	~Gun();

	bool Fire();
};

#endif