#ifndef DRAGONBREATH_H
#define DRAGONBREATH_H

#include "Projectile.h"

class DragonBreath : public Projectile
{
public:
	DragonBreath(Map* map, Vector2 pos, float rotation);
	~DragonBreath();
};

#endif