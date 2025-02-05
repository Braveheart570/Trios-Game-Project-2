#pragma once
#include "PhysEntity.h"
#include "AnimatedGLTexture.h"
#include "Timer.h"
#include "Player.h"
#include "BoxCollider.h"
#include "HeartManager.h"
#include "Random.h"

using namespace SDLFramework;

class Enemy : public PhysEntity {

public:

	Enemy(GLTexture* tex, Player* player, int pts, int health = 1, bool animated = true);
	~Enemy();

	virtual void Render() override;
	virtual void Update() override = 0;

	void Hit(PhysEntity* other) override;

	bool DamageOnContact();

protected:

	Timer* mTimer;

	int mHealth;
	int mPts;
	bool mAnimated;
	int mSpeed;
	bool mDamageOnContact;

	GLTexture* mTexture;

	Player* mPlayer;

};