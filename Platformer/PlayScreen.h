#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include "Level.h"

class PlayScreen
{
public:
	PlayScreen();
	~PlayScreen();

private:
	InputManager* mInput;
	Timer* mTimer;

	static int mStage;
	Level* mLevel;

	Texture* mStageText;

	bool mGameStarted;
	float mStartTimer;
	Texture* mStartText;

	bool mGameOver;
	float mEndTimer;
	Texture* mEndText;

	Texture* mPauseText;
	bool mPaused;

public:
	void UpdateStage();

	bool GameOver() const;

	void Update();
	void Render();
};

#endif