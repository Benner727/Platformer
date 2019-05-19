#ifndef SPELL_H
#define SPELL_H

#include "Actor.h"
#include "AnimatedTexture.h"

class Spell : public Actor
{
public:
	Spell();
	~Spell();

private:
	Timer* mTimer;

protected:
	AnimatedTexture* mSprite;

	Vector2 mSpeed;
	float mDistance;

	void Hit(PhysEntity* other) override;

public:
	void Update();
	void Render();
};

#endif