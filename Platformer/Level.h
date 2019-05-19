#ifndef LEVEL_H
#define LEVEL_H

#include "Background.h"
#include "Interface.h"
#include "Player.h"
#include "Boss.h"

#include "EventManager.h"

class Level
{
public:
	Level(int stage);
	~Level();

private:
	Timer* mTimer;

	Background* mBackground;
	Interface* mInterface;

	Map* mMap;

	Player* mPlayer;
	Boss* mBoss;

	ProjectileManager* mProjectiles;
	EventManager* mEvents;

	Texture* mCursor;

	float mClock;

public:
	bool PlayerDead() const;
	bool BossDead() const;

	float Time() const;

	void Update();
	void Render();
};

#endif