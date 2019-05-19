#pragma once

#include "Projectile.h"

class Beam : public Projectile
{
public:
	Beam(Map* map, Vector2 pos, float rotation, bool first = true);
	~Beam();

private:
	void CreateTrail();
};

