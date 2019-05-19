#ifndef DEMONSTAGE_H
#define DEMONSTAGE_H

#include "Map.h"

class DemonStage : public Map
{
public:
	DemonStage();
	~DemonStage();

private:
	void GenerateFloor();
	void GenerateObstacles();
	void Init();

public:
	Vector2 Spawn();
};

#endif