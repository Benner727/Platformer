#include "StartScreen.h"

StartScreen::StartScreen()
{
	mInput = InputManager::Instance();
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mAudio->PlayMusic("Iwan Gabovitch - Dark Ambience Loop.ogg", -1);

	mBackground = new Background();

	mTitleText = new Texture("Side Scroller", "Roman SD.ttf", 72, { 245, 245, 245 });
	mTitleText->Parent(this);

	mPlayText = new Texture("Play Game", "Roman SD.ttf", 32, { 245, 245, 245 });
	mPlayText->Parent(this);
	mPlayText->Pos(Vector2(0.0f, 160.0f));

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mTextVisible = true;

	mAudioIcon = new Texture("Interface/musicOn.png");
	mAudioIcon->Parent(this);
	mAudioIcon->Pos(Vector2(325.0f, 225.0f));

	mMute = false;

	mSettingIcon = new Texture("Interface/gear.png");
	mSettingIcon->Parent(this);
	mSettingIcon->Pos(Vector2(325.0f, -225.0f));

	mSettings = false;

	Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));
}

StartScreen::~StartScreen()
{
	delete mBackground;
	
	delete mTitleText;
	delete mPlayText;

	delete mAudioIcon;
	delete mSettingIcon;
}

void StartScreen::ToggleMusic()
{
	if (mInput->MouseButtonPressed(InputManager::MOUSE_BUTTON::left))
	{
		Vector2 pos = mInput->MousePos();
		Vector2 bottom = mAudioIcon->Pos() - mAudioIcon->ScaledDimensions();
		Vector2 top = mAudioIcon->Pos() + mAudioIcon->ScaledDimensions();

		if (pos.x < top.x && pos.y < top.y
			&& pos.x > bottom.x && pos.y > bottom.y)
		{
			mMute = !mMute;

			if (!mMute)
			{
				delete mAudioIcon;
				mAudioIcon = new Texture("Interface/musicOn.png");
				mAudioIcon->Parent(this);
				mAudioIcon->Pos(Vector2(325.0f, 225.0f));
				mAudio->ResumeMusic();
			}
			else
			{
				delete mAudioIcon;
				mAudioIcon = new Texture("Interface/musicOff.png");
				mAudioIcon->Parent(this);
				mAudioIcon->Pos(Vector2(325.0f, 225.0f));
				mAudio->PauseMusic();
			}
		}
	}
}

void StartScreen::SwitchScreen(bool out)
{
	if (!mMute)
	{
		if (out)
			mAudio->PauseMusic();
		else
			mAudio->ResumeMusic();
	}
}

bool StartScreen::OpenSettings()
{
	mSettings = false;

	if (mInput->MouseButtonPressed(InputManager::MOUSE_BUTTON::left))
	{
		Vector2 pos = mInput->MousePos();
		Vector2 bottom = mSettingIcon->Pos() - mSettingIcon->ScaledDimensions();
		Vector2 top = mSettingIcon->Pos() + mSettingIcon->ScaledDimensions();

		if (pos.x < top.x && pos.y < top.y
			&& pos.x > bottom.x && pos.y > bottom.y)
		{
			mSettings = true;
		}
	}

	return mSettings;
}

void StartScreen::Update()
{
	mBackground->Update();

	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval)
	{
		mTextVisible = !mTextVisible;
		mBlinkTimer = 0.0f;
	}

	ToggleMusic();
}

void StartScreen::Render()
{
	mBackground->Render();

	mTitleText->Render();

	if (mTextVisible)
		mPlayText->Render();

	mAudioIcon->Render();

	mSettingIcon->Render();
}
