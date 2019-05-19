#ifndef FIREBALL_H
#define FIREBALL_H

#include "Spell.h"

class FireBall : public Spell
{
public:
	FireBall();
	~FireBall();

private:
	void Hit(PhysEntity* other) override;
};

#endif