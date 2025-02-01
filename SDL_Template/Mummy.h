#pragma once
#include "Zombie.h"

class Mummy : public Zombie {

public:

	Mummy(Vector2 pos, Player* player);
	~Mummy();

	void Update() override;
	void Render() override;

private:

	float mFireTime;
	float mFireInterval;

	static const int MAX_BULLETS = 2;
	Bullet* mBullets[MAX_BULLETS];
	void Fire();

};