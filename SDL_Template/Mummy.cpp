#include "Mummy.h"

Mummy::Mummy(Vector2 pos, Player* player) : Zombie(new AnimatedGLTexture("CarpathianSprites.png",143,32,16,24,3,0.5f,Animation::Layouts::Horizontal), pos, player) {
	mHealth = 15;
	mPts = 5000;

	mFireTime = 0.0f;
	mFireInterval = 2.0f;

	mFacingRight = false;

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i] = new Bullet(false);
	}
	
}

Mummy::~Mummy() {
	for (int i = 0; i < MAX_BULLETS; ++i) {
		delete mBullets[i];
		mBullets[i] = nullptr;
	}
}

void Mummy::Update() {

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}

	if (!Active()) {
		return;
	}

	Zombie::Update();

	mFireTime += mTimer->DeltaTime();

	if (mFireTime >= mFireInterval) {
		Fire();
		mFireTime = 0.0f;
	}

}

void Mummy::Render() {
	Enemy::Render();
	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Render();
	}
}

void Mummy::Fire() {

	Vector2 fireDir = ( mPlayer->Position() - Position()).Normalized();

	for (int i = 0; i < MAX_BULLETS; ++i) {
		if (!mBullets[i]->Active()) {
			mBullets[i]->Fire(Position() + Vec2_Up * -30, fireDir);
			break;
		}
	}

}