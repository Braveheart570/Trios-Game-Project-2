#pragma once
#include "Enemy.h"

class Fishman : public Enemy {

public:

	Fishman(Vector2 pos, Player* player);
	~Fishman();

	void Update() override;
	void Render() override;

private:

	const int mWanderDist = 100;
	int nWanderXRight;
	int mWanderXLeft;
	bool mFacingRight;

	int mYTrigger;
	int mPlayerOriginOffset;

	float mFireTime;
	float mFireInterval;

	static const int MAX_BULLETS = 2;
	Bullet* mBullets[MAX_BULLETS];
	void Fire();

};