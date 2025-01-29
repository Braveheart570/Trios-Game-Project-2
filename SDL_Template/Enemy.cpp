#include "Enemy.h"

Enemy::Enemy(GLTexture* tex, int pts, int health, bool animated) : PhysEntity(){

	mPts = pts;
	mHealth = health;
	mAnimated = animated;
	mTexture = tex;
	mTexture->Parent(this);
	mTexture->Scale(Vec2_One * 5);
	mSpeed = 80;

	mTimer = Timer::Instance();
}

Enemy::~Enemy() {
	mTimer = nullptr;
}

void Enemy::Render() {
	mTexture->Render();
}