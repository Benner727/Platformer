#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "AudioManager.h"
#include "AnimatedTexture.h"
#include "Actor.h"

class Projectile : public Actor
{
public:
	Projectile(Map* map, Vector2 pos, float rotation);
	~Projectile();

private:
	Timer* mTimer;

private:
	float mHorizontalSpeed;
	float mVerticalSpeed;

protected:
	AudioManager* mAudio;

	AnimatedTexture* mSprite;

	float mSpeed;
	float mGravity;
	float mDistance;

	void Hit(PhysEntity* other) override;

public:
	bool CleanUp();

	void Update();
	void Render();
};

#endif