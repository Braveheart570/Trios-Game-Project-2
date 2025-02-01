#pragma once
#include "Enemy.h"

class Pumpkin : public Enemy {

public:

	Pumpkin(Vector2 pos, Player* player);
	~Pumpkin();

	void Update() override;
	void Render() override;

protected:

	bool mFacingRight;

	int mYTrigger;
	int mPlayerOriginOffset;

	bool mFiring;
	float mFireTexTime;
	float mFireTexDur;

	float mFireTime;
	float mFireInterval;

	GLTexture* mFiringTex;

	static const int MAX_BULLETS = 16;
	Bullet* mBullets[MAX_BULLETS];
	 virtual void Fire();

	 Pumpkin(GLTexture* tex, GLTexture* firTex, Vector2 pos, Player* player);
};