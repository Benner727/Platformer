#ifndef ICICLE_H
#define ICICLE_H

#include "Spell.h"

class Icicle : public Spell
{
public:
	Icicle();
	~Icicle();

private:
	void Hit(PhysEntity* other) override;
};

#endif