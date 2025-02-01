#pragma once
#include "Enemy.h"

class Pumpkin : public Enemy {

public:

	Pumpkin(Vector2 pos, Player* player);
	~Pumpkin();

	void Update() override;
	void Render() override;

private:

	bool mFacingRight;

	int mYTrigger;
	int mPlayerOriginOffset;

	bool mFiring = true;
	float mFireTexTime;
	float mFireTexDur;

	float mFireTime;
	float mFireInterval;

	GLTexture* mFiringTex;

	static const int MAX_BULLETS = 2;
	Bullet* mBullets[MAX_BULLETS];
	void Fire();

};