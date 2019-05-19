#include "Interface.h"

Interface::Interface(int fullHealth)
	: mFullHealth(fullHealth)
{
	mBlankBar = new Texture("blankbar.png");
	mBlankBar->Parent(this);
	mBlankBar->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.42f, Graphics::SCREEN_HEIGHT * 0.05f));

	float barPos = (mBlankBar->Pos().x + mBlankBar->ScaledDimensions().x * 0.5f) - 9.0f;

	for (int i = 0; i < 56; i++)
	{
		mHealthBar.push_back(new Texture("healthbar.png"));
		mHealthBar.back()->Parent(this);
		mHealthBar.back()->Pos(Vector2(barPos - i * 10.0f, mBlankBar->Pos().y));
	}

	Time(0.0f);

	mAmmoValue = 0;
}

Interface::~Interface()
{
	delete mBlankBar;

	for (std::deque<Texture*>::iterator it = mHealthBar.begin(); it != mHealthBar.end(); ++it)
		delete * it;

	for (std::vector<Texture*>::iterator it = mTime.begin(); it != mTime.end(); ++it)
		delete * it;

	for (std::vector<Texture*>::iterator it = mAmmo.begin(); it != mAmmo.end(); ++it)
		delete * it;

	for (std::vector<Texture*>::iterator it = mClip.begin(); it != mClip.end(); ++it)
		delete * it;
}

void Interface::Health(int health)
{
	float barPos = (mBlankBar->Pos(local).x + mBlankBar->ScaledDimensions().x * 0.5f) - 9.0f;
	int newSize = 56.0f * ((float)health / mFullHealth);

	for (std::deque<Texture*>::iterator it = mHealthBar.begin(); it != mHealthBar.end();)
	{
		if (mHealthBar.size() > newSize)
		{
			delete * it;
			it = mHealthBar.erase(it);
		}
		else if (mHealthBar.size() < newSize)
		{
			mHealthBar.insert(mHealthBar.begin(), new Texture("healthbar.png"));
			mHealthBar.front()->Parent(this);
			mHealthBar.front()->Pos(Vector2(barPos - (56 - mHealthBar.size()) * 10.0f, mBlankBar->Pos().y));
			return;
		}
		else
			return;
	}
}

void Interface::Time(float clock)
{
	for (std::vector<Texture*>::iterator it = mTime.begin(); it != mTime.end(); ++it)
		delete * it;
	mTime.clear();

	int time = (int)clock;
	std::string str = std::to_string(time / 60);
	str.push_back(':');

	if (time % 60 < 10)
		str.push_back('0');

	str += std::to_string(time % 60);

	int lastIndex = str.length() - 1;

	for (int i = 0; i <= lastIndex; i++)
	{
		mTime.push_back(new Texture(std::string(1, str[i]), "Roman SD.ttf", 32, { 155, 155, 0 }));
		mTime.back()->Parent(this);

		if (i < lastIndex / 2)
			mTime[i]->Pos(Vector2(-24.0f * (lastIndex / 2 - i) + Graphics::SCREEN_WIDTH * 0.88f, Graphics::SCREEN_HEIGHT * 0.05f));
		else
			mTime[i]->Pos(Vector2(24.0f * (i - lastIndex / 2) + Graphics::SCREEN_WIDTH * 0.88f, Graphics::SCREEN_HEIGHT * 0.05f));
	}
}

void Interface::Clip(const int& clip, const int& clipSize)
{
	if (mClip.size() != clip)
	{
		for (std::vector<Texture*>::iterator it = mClip.begin(); it != mClip.end(); ++it)
			delete * it;
		mClip.clear();

		for (int i = clipSize - clip; i < clipSize; i++)
		{
			mClip.push_back(new Texture("Bullet.png", 8, 0, 8, 8));
			mClip.back()->Parent(this);
			mClip.back()->Rotate(180.0f);
			mClip.back()->Pos(Vector2(Graphics::SCREEN_WIDTH - (clipSize - i) * 8, Graphics::SCREEN_HEIGHT * 0.95f));
		}
	}
}

void Interface::Ammo(const int& ammo)
{
	if (mAmmoValue != ammo)
	{
		for (std::vector<Texture*>::iterator it = mAmmo.begin(); it != mAmmo.end(); ++it)
			delete * it;
		mAmmo.clear();

		mAmmoValue = ammo;

		std::string str = std::to_string(ammo);

		for (int i = 0; i < str.size(); i++)
		{
			mAmmo.push_back(new Texture(std::string(1, str[i]), "Roman SD.ttf", 24, { 255, 255, 255 }));
			mAmmo.back()->Parent(this);
			mAmmo.back()->Pos(Vector2(Graphics::SCREEN_WIDTH - (str.size() - i) * 12, Graphics::SCREEN_HEIGHT * 0.98f));
		}
	}
}

void Interface::Update()
{
	Pos(Vector2(Graphics::Instance()->Camera()->x, Graphics::Instance()->Camera()->y));
}

void Interface::Render()
{
	mBlankBar->Render();

	for (const auto& healthbar : mHealthBar)
		healthbar->Render();

	for (const auto& time : mTime)
		time->Render();

	for (const auto& clip : mClip)
		clip->Render();

	for (const auto& ammo : mAmmo)
		ammo->Render();
}
