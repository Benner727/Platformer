#ifndef SETTINGSCREEN_H
#define SETTINGSCREEN_H

#include <vector>

#include "InputManager.h"
#include "AudioManager.h"
#include "Texture.h"

class SettingScreen : public GameEntity
{
public:
	SettingScreen();
	~SettingScreen();

private:
	InputManager* mInput;
	AudioManager* mAudio;

	Texture* mSettingLabel;

	Texture* mVolumeLabel;
	Texture* mMinusIcon;
	Texture* mPlusIcon;

	int mVolume;
	std::vector<Texture*> mVolumeText;

	Texture* mControlLabels[7];
	Texture* mControlText[7];

	void DecreaseVolume();
	void IncreaseVolume();

	void UpdateVolume();

public:
	void Update();
	void Render();
};

#endif