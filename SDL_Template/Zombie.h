#pragma once
#include "Enemy.h"

class Zombie : public Enemy {

public:

	Zombie(Vector2 pos, Player* player);
	~Zombie();

	void Update() override;


private:

	const int mWanderDist = 100;
	int nWanderXRight;
	int mWanderXLeft;
	bool mFacingRight;

};