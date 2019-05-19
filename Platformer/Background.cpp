#include "Background.h"

Background::Background()
{
	mFirst = new Texture("background.png");
	mFirst->Pos(Vector2(mFirst->Pos().x + mFirst->ScaledDimensions().x * 0.5f, mFirst->Pos().y + mFirst->ScaledDimensions().y * 0.5f));

	mSecond = new Texture("background.png");
	mSecond->Pos(Vector2(mFirst->Pos().x + mFirst->ScaledDimensions().x, mFirst->Pos().y));

	mPrevPos = Vector2(Graphics::Instance()->Camera()->x, Graphics::Instance()->Camera()->y);

	mForeground = new Foreground();
}

Background::~Background()
{
	delete mFirst;
	delete mSecond;

	delete mForeground;
}

void Background::Update()
{
	float distance = (Graphics::Instance()->Camera()->x - mPrevPos.x) * 0.25f;
	mFirst->Translate(VEC2_RIGHT * distance);
	mSecond->Translate(VEC2_RIGHT * distance);

	if (mFirst->Pos().x + mFirst->ScaledDimensions().x * 0.5f < Graphics::Instance()->Camera()->x)
		mFirst->Pos(Vector2(mSecond->Pos().x + mFirst->ScaledDimensions().x, mFirst->Pos().y));
	else if (mFirst->Pos().x - mFirst->ScaledDimensions().x * 0.5f > Graphics::Instance()->Camera()->x + Graphics::SCREEN_WIDTH)
		mFirst->Pos(Vector2(mSecond->Pos().x - mFirst->ScaledDimensions().x, mFirst->Pos().y));

	if (mSecond->Pos().x + mFirst->ScaledDimensions().x * 0.5f < Graphics::Instance()->Camera()->x)
		mSecond->Pos(Vector2(mFirst->Pos().x + mFirst->ScaledDimensions().x, mFirst->Pos().y));
	else if (mSecond->Pos().x - mFirst->ScaledDimensions().x * 0.5f > Graphics::Instance()->Camera()->x + Graphics::SCREEN_WIDTH)
		mSecond->Pos(Vector2(mFirst->Pos().x - mFirst->ScaledDimensions().x, mFirst->Pos().y));

	mPrevPos = Vector2(Graphics::Instance()->Camera()->x, Graphics::Instance()->Camera()->y);

	mForeground->Update();
}

void Background::Render()
{
	mFirst->Render();
	mSecond->Render();

	mForeground->Render();
}