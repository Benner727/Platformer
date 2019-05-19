#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "StartScreen.h"
#include "PlayScreen.h"
#include "SettingScreen.h"

class ScreenManager
{
private:
	enum SCREENS { start, play, settings };

	static ScreenManager* sInstance;

	ScreenManager();
	~ScreenManager();

	InputManager* mInput;

	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;
	SettingScreen* mSettingScreen;

	SCREENS mCurrentScreen;

public:
	static ScreenManager* Instance();

	static void Release();

	void Update();
	void Render();
};

#endif