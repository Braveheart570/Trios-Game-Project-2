#pragma once
#include "PhysEntity.h"
#include "AnimatedGLTexture.h"
#include "Timer.h"

using namespace SDLFramework;

class Enemy : public PhysEntity {

public:

	Enemy(GLTexture* tex, int pts, int health = 1, bool animated = true);
	~Enemy();

	void Render() override;
	virtual void Update() override = 0;

protected:

	Timer* mTimer;

	int mHealth;
	int mPts;
	bool mAnimated;
	int mSpeed;

	GLTexture* mTexture;

};