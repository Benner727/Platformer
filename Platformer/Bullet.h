#ifndef BULLET_H
#define BULLET_H

#include "Projectile.h"

class Bullet : public Projectile
{
public:
	Bullet(Map* map, Vector2 pos, float rotation);
	~Bullet();
};

#endif