#include "Enemy.h"

Enemy::Enemy(GLTexture* tex, Player* player, int pts, int health, bool animated) : PhysEntity(){

	mPts = pts;
	mHealth = health;
	mAnimated = animated;
	mTexture = tex;
	mTexture->Parent(this);
	mTexture->Scale(Vec2_One * 5);
	mSpeed = 80;
	mPlayer = player;

	mTimer = Timer::Instance();
}

Enemy::~Enemy() {
	mTimer = nullptr;
	mPlayer = nullptr;
}

void Enemy::Render() {
	if (!Active()) {
		return;
	}
	mTexture->Render();
	mColliders[0]->Render();
}

void Enemy::Hit(PhysEntity* other) {
	if (dynamic_cast<Bullet*>(other)) {
		mHealth--;
		if (mHealth <= 0) {
			Active(false);
		}
		
	}
}