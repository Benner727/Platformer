#ifndef DRAGONSTAGE_H
#define DRAGONSTAGE_H

#include "Map.h"

class DragonStage : public Map
{
public:
	DragonStage();
	~DragonStage();

private:
	void GenerateFloor();
	void Init();

public:
	Vector2 Spawn();
};

#endif