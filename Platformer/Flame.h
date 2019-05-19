#pragma once

#include "Projectile.h"

class Flame : public Projectile
{
public:
	Flame(Map* map, Vector2 pos, float rotation);
	~Flame();
};

