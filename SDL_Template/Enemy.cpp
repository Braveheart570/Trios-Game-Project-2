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
	mDamageOnContact = true;

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
			mPlayer->AddScore(mPts);
			Active(false);
		}
		
	}
	else if (mDamageOnContact && !dynamic_cast<Player*>(other)->Invulnerable()) {
		mPlayer->TakeHit();
	}
}

bool Enemy::DamageOnContact() {
	return mDamageOnContact;
}