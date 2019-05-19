#include "Event.h"

Event::Event(Map* map, Vector2 pos)
	: Actor(map)
{
	mAudio = AudioManager::Instance();

	mSprite = nullptr;
}

Event::~Event()
{
	delete mSprite;
}

void Event::Hit(PhysEntity * other)
{
	Active(false);
}

bool Event::CleanUp()
{
	return !(Active() || mSprite->IsAnimating());
}

void Event::Update()
{
	mSprite->Update();
}

void Event::Render()
{
	mSprite->Render();
}
