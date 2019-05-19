#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Foreground.h"

class Background
{
public:
	Background();
	~Background();

private:
	Texture* mFirst;
	Texture* mSecond;

	Vector2 mPrevPos;

	Foreground* mForeground;

public:
	void Update();
	void Render();
};

#endif