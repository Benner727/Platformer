#ifndef FOREGROUND_H
#define FOREGROUND_H

#include "Texture.h"

class Foreground
{
public:
	Foreground();
	~Foreground();

private:
	Texture* mFirst;
	Texture* mSecond;

public:
	void Update();
	void Render();
};

#endif