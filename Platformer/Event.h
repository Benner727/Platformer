#pragma once

#include "Actor.h"
#include "AnimatedTexture.h"
#include "AudioManager.h"

class Event : public Actor
{
public:
	Event(Map* map, Vector2 pos);
	~Event();

protected:
	AudioManager* mAudio;

	AnimatedTexture* mSprite;

	void Hit(PhysEntity* other) override;

public:
	virtual bool CleanUp();

	virtual void Update();
	virtual void Render();
};