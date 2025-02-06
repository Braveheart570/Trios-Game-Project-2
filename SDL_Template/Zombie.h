#pragma once
#include "Enemy.h"

class Zombie : public Enemy {

public:

	Zombie(Vector2 pos, Player* player);

	~Zombie();

	virtual void Update() override;


protected:

	const int mWanderDist = 60;
	int nWanderXRight;
	int mWanderXLeft;
	bool mFacingRight;

	Zombie(AnimatedGLTexture* tex, Vector2 pos, Player* player);

};