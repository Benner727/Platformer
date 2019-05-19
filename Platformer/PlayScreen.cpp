#include "PlayScreen.h"

#include "PhysicsManager.h"

int PlayScreen::mStage = 0;

PlayScreen::PlayScreen()
{
	mInput = InputManager::Instance();
	mTimer = Timer::Instance();

	mLevel = new Level(mStage);

	mStageText = new Texture("Stage " + std::to_string(mStage + 1), "Roman SD.ttf", 48, { 0, 139, 0 });
	mStageText->Pos(Vector2(Graphics::Instance()->Camera()->x + Graphics::Instance()->Camera()->w * 0.5f, Graphics::Instance()->Camera()->y + Graphics::Instance()->Camera()->h * 0.4f));

	mPauseText = new Texture("Paused", "Roman SD.ttf", 48, { 0, 0, 139 });
	mPauseText->Pos(Vector2(Graphics::Instance()->Camera()->x + Graphics::Instance()->Camera()->w * 0.5f, Graphics::Instance()->Camera()->y + Graphics::Instance()->Camera()->h * 0.5f));

	mPaused = false;

	mGameStarted = false;
	mStartTimer = 1.5f;
	mStartText = new Texture("Begin!", "Roman SD.ttf", 48, { 0, 139, 0 });
	mStartText->Pos(Vector2(Graphics::Instance()->Camera()->x + Graphics::Instance()->Camera()->w * 0.5f, Graphics::Instance()->Camera()->y + Graphics::Instance()->Camera()->h * 0.5f));

	mGameOver = false;
	mEndTimer = 1.0f;
	mEndText = nullptr;
}


PlayScreen::~PlayScreen()
{
	delete mLevel;

	delete mStageText;
	delete mPauseText;
	delete mStartText;
	delete mEndText;
}

void PlayScreen::UpdateStage()
{
	mStage > 1 ? mStage = 0 : mStage++;
}

bool PlayScreen::GameOver() const
{
	return mGameOver;
}

void PlayScreen::Update()
{
	if (mGameStarted)
	{
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			mPaused = !mPaused;
			mPauseText->Pos(Vector2(Graphics::Instance()->Camera()->x + Graphics::Instance()->Camera()->w * 0.5f, Graphics::Instance()->Camera()->y + Graphics::Instance()->Camera()->h * 0.5f));

			mPaused ? SDL_ShowCursor(SDL_ENABLE) : SDL_ShowCursor(SDL_DISABLE);
		}

		if (!mPaused)
		{
			if (!mGameOver && (mLevel->PlayerDead() || mLevel->BossDead()))
			{
				if (mEndTimer == 1.0f)
				{
					if (mLevel->BossDead())
					{
						mEndText = new Texture("Victory", "Roman SD.ttf", 48, { 139, 0, 0 });
						UpdateStage();
					}
					else if (mLevel->PlayerDead())
						mEndText = new Texture("Defeat", "Roman SD.ttf", 48, { 139, 0, 0 });
					mEndText->Pos(Vector2(Graphics::Instance()->Camera()->x + Graphics::Instance()->Camera()->w * 0.5f, Graphics::Instance()->Camera()->y + Graphics::Instance()->Camera()->h * 0.5f));
				}

				mEndTimer -= mTimer->DeltaTime();

				if (mEndTimer <= 0.0f)
					mGameOver = true;
			}
			else
				mLevel->Update();
		}
	}
	else
	{
		mStartTimer -= mTimer->DeltaTime();

		if (mStartTimer <= 0.0f)
			mGameStarted = true;
	}
}

void PlayScreen::Render()
{
	mLevel->Render();

	if (mPaused)
		mPauseText->Render();
	else if (!mGameStarted)
	{
		mStageText->Render();
		if (mStartTimer <= 1.0f)
			mStartText->Render();
	}
	else if (!mGameOver && (mLevel->PlayerDead() || mLevel->BossDead()))
		if (mEndText) mEndText->Render();
}
