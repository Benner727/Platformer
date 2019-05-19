#include "Foreground.h"

Foreground::Foreground()
{
	mFirst = new Texture("foreground.png");
	mFirst->Pos(Vector2(mFirst->Pos().x + mFirst->ScaledDimensions().x * 0.5f, mFirst->Pos().y + mFirst->ScaledDimensions().y * 0.5f));

	mSecond = new Texture("foreground.png");
	mSecond->Pos(Vector2(mFirst->Pos().x + mFirst->ScaledDimensions().x, mFirst->Pos().y));
}

Foreground::~Foreground()
{
	delete mFirst;
	delete mSecond;
}

void Foreground::Update()
{
	if (mFirst->Pos().x + mFirst->ScaledDimensions().x * 0.5f < Graphics::Instance()->Camera()->x)
		mFirst->Pos(Vector2(mSecond->Pos().x + mFirst->ScaledDimensions().x, mFirst->Pos().y));
	else if (mFirst->Pos().x - mFirst->ScaledDimensions().x * 0.5f > Graphics::Instance()->Camera()->x + Graphics::SCREEN_WIDTH)
		mFirst->Pos(Vector2(mSecond->Pos().x - mFirst->ScaledDimensions().x, mFirst->Pos().y));

	if (mSecond->Pos().x + mFirst->ScaledDimensions().x * 0.5f < Graphics::Instance()->Camera()->x)
		mSecond->Pos(Vector2(mFirst->Pos().x + mFirst->ScaledDimensions().x, mFirst->Pos().y));
	else if (mSecond->Pos().x - mFirst->ScaledDimensions().x * 0.5f > Graphics::Instance()->Camera()->x + Graphics::SCREEN_WIDTH)
		mSecond->Pos(Vector2(mFirst->Pos().x - mFirst->ScaledDimensions().x, mFirst->Pos().y));
}

void Foreground::Render()
{
	mFirst->Render();
	mSecond->Render();
}