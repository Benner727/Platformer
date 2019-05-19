#ifndef INTERFACE_H
#define INTERACE_H

#include "Texture.h"
#include <deque>
#include <vector>

class Interface : public GameEntity
{
public:
	Interface(int fullHealth);
	~Interface();

private:
	Texture* mBlankBar;
	std::deque<Texture*> mHealthBar;
	int mFullHealth;

	std::vector<Texture*> mTime;

	std::vector<Texture*> mClip;

	std::vector<Texture*> mAmmo;
	int mAmmoValue;

public:
	void Health(int health);
	void Time(float clock);

	void Clip(const int& clip, const int& clipSize);
	void Ammo(const int& ammo);

	void Update();
	void Render();
};

#endif