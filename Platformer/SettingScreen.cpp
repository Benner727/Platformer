#include "SettingScreen.h"

SettingScreen::SettingScreen()
{
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mSettingLabel = new Texture("Config", "Roman SD.ttf", 54, { 255, 255, 255 });
	mSettingLabel->Parent(this);
	mSettingLabel->Pos(Vector2(0.0f, -200.0f));

	mVolumeLabel = new Texture("Volume:", "Roman SD.ttf", 36, { 208, 209, 211 });
	mVolumeLabel->Parent(this);
	mVolumeLabel->Pos(Vector2(-15.0f - mVolumeLabel->ScaledDimensions().x * 0.5f, -125.0f));

	mMinusIcon = new Texture("Interface/minus.png");
	mMinusIcon->Parent(this);
	mMinusIcon->Pos(Vector2(125.0f, -125.0f));

	mPlusIcon = new Texture("Interface/plus.png");
	mPlusIcon->Parent(this);
	mPlusIcon->Pos(Vector2(175.0f, -125.0f));

	mVolume = mAudio->Volume();
	UpdateVolume();

	mControlLabels[0] = new Texture("Walk Left:", "Roman SD.ttf", 36, { 208, 209, 211 });
	mControlLabels[1] = new Texture("Walk Right:", "Roman SD.ttf", 36, { 208, 209, 211 });
	mControlLabels[2] = new Texture("[Double] Jump:", "Roman SD.ttf", 36, { 208, 209, 211 });
	mControlLabels[3] = new Texture("Cancel Jump:", "Roman SD.ttf", 36, { 208, 209, 211 });
	mControlLabels[4] = new Texture("Reload:", "Roman SD.ttf", 36, { 208, 209, 211 });
	mControlLabels[5] = new Texture("Swap Weapon:", "Roman SD.ttf", 36, { 208, 209, 211 });
	mControlLabels[6] = new Texture("Toggle Camera:", "Roman SD.ttf", 36, { 208, 209, 211 });

	mControlText[0] = new Texture("A", "Roman SD.ttf", 36, { 0, 139, 0 });
	mControlText[1] = new Texture("D", "Roman SD.ttf", 36, { 0, 139, 0 });
	mControlText[2] = new Texture("W", "Roman SD.ttf", 36, { 0, 139, 0 });
	mControlText[3] = new Texture("S", "Roman SD.ttf", 36, { 0, 139, 0 });
	mControlText[4] = new Texture("R", "Roman SD.ttf", 36, { 0, 139, 0 });
	mControlText[5] = new Texture("Q | E", "Roman SD.ttf", 36, { 0, 139, 0 });
	mControlText[6] = new Texture("Space Bar", "Roman SD.ttf", 36, { 0, 139, 0 });

	for (int i = 0; i < 7; i++)
	{
		mControlLabels[i]->Parent(this);
		mControlLabels[i]->Pos(Vector2(-15.0f - mControlLabels[i]->ScaledDimensions().x * 0.5f, -75.0f + i * 50.0f));

		mControlText[i]->Parent(this);
		mControlText[i]->Pos(Vector2(140.0f, -75.0f + i * 50.0f));
	}

	Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));
}

SettingScreen::~SettingScreen()
{
	delete mSettingLabel;

	delete mVolumeLabel;
	delete mMinusIcon;
	delete mPlusIcon;

	for (std::vector<Texture*>::iterator it = mVolumeText.begin(); it != mVolumeText.end(); ++it)
		delete * it;

	for (int i = 0; i < 7; i++)
	{
		delete mControlLabels[i];
		delete mControlText[i];
	}
}

void SettingScreen::DecreaseVolume()
{
	if (mInput->MouseButtonPressed(InputManager::MOUSE_BUTTON::left))
	{
		Vector2 pos = mInput->MousePos();
		Vector2 bottom = mMinusIcon->Pos() - mMinusIcon->ScaledDimensions() * 0.5f;
		Vector2 top = mMinusIcon->Pos() + mMinusIcon->ScaledDimensions() * 0.5f;

		if (pos.x < top.x && pos.y < top.y
			&& pos.x > bottom.x && pos.y > bottom.y)
		{
			if (mVolume > 0)
			{
				mVolume--;
				mMinusIcon->FlashRed();
				UpdateVolume();
			}
		}
	}
}

void SettingScreen::IncreaseVolume()
{
	if (mInput->MouseButtonPressed(InputManager::MOUSE_BUTTON::left))
	{
		Vector2 pos = mInput->MousePos();
		Vector2 bottom = mPlusIcon->Pos() - mPlusIcon->ScaledDimensions() * 0.5f;
		Vector2 top = mPlusIcon->Pos() + mPlusIcon->ScaledDimensions() * 0.5f;

		if (pos.x < top.x && pos.y < top.y
			&& pos.x > bottom.x && pos.y > bottom.y)
		{
			if (mVolume < 100)
			{
				mVolume++;
				mPlusIcon->FlashRed();
				UpdateVolume();
			}
		}
	}
}

void SettingScreen::UpdateVolume()
{
	for (std::vector<Texture*>::iterator it = mVolumeText.begin(); it != mVolumeText.end(); ++it)
		delete * it;
	mVolumeText.clear();

	std::string str = std::to_string(mVolume);
	int lastIndex = str.length() - 1;

	for (int i = 0; i <= lastIndex; i++)
	{
		mVolumeText.push_back(new Texture(std::string(1, str[i]), "Roman SD.ttf", 36, { 155, 155, 0 }));
		mVolumeText.back()->Parent(this);

		if (i < lastIndex / 2)
			mVolumeText[i]->Pos(Vector2(60.0f + -24.0f * (lastIndex / 2 - i), -125.0f));
		else
			mVolumeText[i]->Pos(Vector2(60.0f + 24.0f * (i - lastIndex / 2), -125.0f));
	}

	mAudio->Volume(mVolume);
}

void SettingScreen::Update()
{
	DecreaseVolume();
	IncreaseVolume();
}

void SettingScreen::Render()
{
	mSettingLabel->Render();

	mVolumeLabel->Render();
	mMinusIcon->Render();
	mPlusIcon->Render();
	for (const auto& volume : mVolumeText)
		volume->Render();

	for (const auto& label : mControlLabels)
		label->Render();

	for (const auto& text : mControlText)
		text->Render();
}
