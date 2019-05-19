#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "InputManager.h"
#include "Timer.h"
#include "AudioManager.h"
#include "Background.h"

class StartScreen : public GameEntity
{
public:
	StartScreen();
	~StartScreen();

private:
	InputManager* mInput;
	Timer* mTimer;
	AudioManager* mAudio;

	Background* mBackground;

	Texture* mTitleText;
	Texture* mPlayText;

	float mBlinkTimer;
	float mBlinkInterval;
	bool mTextVisible;

	Texture* mAudioIcon;
	bool mMute;

	Texture* mSettingIcon;
	bool mSettings;

	void ToggleMusic();

public:
	void SwitchScreen(bool out);
	bool OpenSettings();

	void Update();
	void Render();
};

#endif