#include "Level.h"

#include "Demon.h"
#include "DemonStage.h"

#include "TwinDragon.h"
#include "DragonStage.h"

Level::Level(int stage)
{
	mTimer = Timer::Instance();

	mProjectiles = ProjectileManager::Instance();
	mEvents = EventManager::Instance();

	switch (stage)
	{
	case 0:
		mMap = new DragonStage();
		break;
	case 1:
		mMap = new DemonStage();
		break;
	}
	Graphics::Instance()->Camera(mMap->Spawn(), true);

	mBackground = new Background();
	mBackground->Update();

	mPlayer = new Player(mMap);
	mPlayer->Pos(mMap->Spawn());
	
	switch (stage)
	{
	case 0:
		mBoss = new TwinDragon(mMap, mPlayer);
		break;
	case 1:
		mBoss = new Demon(mMap, mPlayer);
		break;
	}

	mInterface = new Interface(mBoss->FullHealth());
	mInterface->Update();

	SDL_ShowCursor(SDL_DISABLE);
	mCursor = new Texture("crosshair.png");

	mClock = 0.0f;
}

Level::~Level()
{
	mProjectiles->Release();
	mEvents->Release();

	delete mBackground;
	delete mInterface;
	delete mPlayer;
	delete mBoss;
	delete mMap;
	delete mCursor;

	Graphics::Instance()->Camera(VEC2_ZERO);
	SDL_ShowCursor(SDL_ENABLE);
}

bool Level::PlayerDead() const
{
	return mPlayer->Dead();
}

bool Level::BossDead() const
{
	return mBoss->Dead();
}

float Level::Time() const
{
	return mClock;
}

void Level::Update()
{
	mBackground->Update();

	mMap->Update();

	mBoss->Update();

	mPlayer->Update();

	mProjectiles->Update();
	mEvents->Update();

	mClock += mTimer->DeltaTime();

	mInterface->Health(mBoss->Health());
	mInterface->Time(mClock);
	mInterface->Clip(mPlayer->Clip(), mPlayer->ClipSize());
	mInterface->Ammo(mPlayer->Ammo());
	mInterface->Update();

	mCursor->Pos(InputManager::Instance()->MousePos() + Vector2(Graphics::Instance()->Camera()->x, Graphics::Instance()->Camera()->y));
	if (InputManager::Instance()->MouseButtonPressed(InputManager::MOUSE_BUTTON::left)) mCursor->FlashRed();
}

void Level::Render()
{
	mBackground->Render();

	mInterface->Render();

	mMap->Render();

	mBoss->Render();

	mPlayer->Render();

	mProjectiles->Render();
	mEvents->Render();

	mCursor->Render();
}