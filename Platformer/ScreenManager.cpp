#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new ScreenManager();

	return sInstance;
}

void ScreenManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager()
{
	mInput = InputManager::Instance();
	
	mStartScreen = new StartScreen();
	mPlayScreen = nullptr;
	mSettingScreen = nullptr;

	mCurrentScreen = start;
}

ScreenManager::~ScreenManager()
{
	delete mStartScreen;
	delete mPlayScreen;
}

void ScreenManager::Update()
{
	switch (mCurrentScreen)
	{
	case start:

		mStartScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN) || mInput->KeyPressed(SDL_SCANCODE_SPACE))
		{
			mStartScreen->SwitchScreen(true);

			mPlayScreen = new PlayScreen();
			mCurrentScreen = play;
		}
		else if (mInput->MouseButtonPressed(InputManager::MOUSE_BUTTON::left) && mStartScreen->OpenSettings())
		{
			mSettingScreen = new SettingScreen();
			mCurrentScreen = settings;
		}

		break;
	case play:

		if (mPlayScreen->GameOver())
		{
			delete mPlayScreen;
			mPlayScreen = nullptr;

			mStartScreen->SwitchScreen(false);

			mCurrentScreen = start;
		}
		else
			mPlayScreen->Update();

		break;
	case settings:

		mSettingScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			delete mSettingScreen;
			mSettingScreen = nullptr;

			mCurrentScreen = start;
		}

		break;
	}
}

void ScreenManager::Render()
{
	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Render();
		break;
	case play:
		mPlayScreen->Render();
		break;
	case settings:
		mSettingScreen->Render();
		break;
	}
}