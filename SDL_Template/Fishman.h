#pragma once
#include "Zombie.h"

class Fishman : public Zombie {

public:

	Fishman(Vector2 pos, Player* player);
	~Fishman();

	void Update() override;
	void Render() override;

private:

	int mYTrigger;
	int mPlayerOriginOffset;

	float mFireTime;
	float mFireInterval;

	static const int MAX_BULLETS = 2;
	Bullet* mBullets[MAX_BULLETS];
	void Fire();

};