#include "Timer.h"

Timer* Timer::sInstance = nullptr;

Timer* Timer::Instance()
{
	if (sInstance == nullptr)
		sInstance = new Timer();

	return sInstance;
}

void Timer::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

Timer::Timer()
{
	mStartTicks = 0;
	mEndTicks = 0;
	mDeltaTime = 0.0f;
}


Timer::~Timer()
{

}

float Timer::DeltaTime()
{
	return mDeltaTime / 1000.0f;
}
#include <iostream>
void Timer::Update()
{
	mStartTicks = SDL_GetTicks();
	mDeltaTime = SDL_GetTicks() - mEndTicks;
	mEndTicks = mStartTicks;

	static int x = 0;
	x++;

	if (mDeltaTime > 17)
	{
		std::cout << x << " : " << mDeltaTime << std::endl;
		x = 0;
	}
}