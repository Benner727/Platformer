#pragma once

#include "Event.h"

class Explosion : public Event
{
public:
	Explosion(Map* map, Vector2 pos);
	~Explosion();

private:
	bool mStarted;
	bool mHit;

	void Hit(PhysEntity* other) override;

public:
	bool CleanUp();

	void Update();
	void Render();
};

