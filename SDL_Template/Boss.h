#pragma once
#include "Enemy.h"

class Boss : public Enemy {

public:

	Boss(Vector2 pos, Player* player);
	~Boss();

	void Update() override;
	void Render() override;

private:

	bool mAtemptStationaryState;
	float mStateTime;
	float mStateDur;

	bool mMoving;
	float mSpeed;

	float mFireTime;
	float mFireIntervalSingle;
	float mFireIntervalRing;

	bool mFiring;
	float mFireTexTime;
	float mFireTexDur;

	GLTexture* mFiringTex;


	static const int MAX_BULLETS = 24;
	Bullet* mBullets[MAX_BULLETS];
	void FireSingle();
	void FireRing();
};