#include "Fishman.h"

Fishman::Fishman(Vector2 pos, Player* player) : Zombie(new AnimatedGLTexture("CarpathianSprites.png", 100, 0, 16, 16, 2, 0.75f, Animation::Layouts::Horizontal),pos, player){

	mHealth = 3;
	mPts = 400;

	mYTrigger = 100;
	mPlayerOriginOffset = -30;

	mFireTime = 0.0f;
	mFireInterval = 2.0f;


	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i] = new Bullet(false);
	}

}

Fishman::~Fishman() {
	for (int i = 0; i < MAX_BULLETS; ++i) {
		delete mBullets[i];
		mBullets[i] = nullptr;
	}
}

void Fishman::Update() {

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}

	if (!Active()) {
		return;
	}

	Zombie::Update();

	mFireTime += mTimer->DeltaTime();
	
	if (mFireTime >= mFireInterval) {
		
		if ((abs(mPlayer->Position().y - Position().y) >= mYTrigger)) {
			return;
		}
		if (mFacingRight && mPlayer->Position().x > Position().x || !mFacingRight && mPlayer->Position().x < Position().x) {
			Fire();
			
			mFireTime = 0.0f;
		}

	}

}

void Fishman::Render() {
	Zombie::Render();
	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Render();
	}
}

void Fishman::Fire() {

	for (int i = 0; i < MAX_BULLETS; ++i) {
		if (!mBullets[i]->Active()) {
			mBullets[i]->Fire(Position() + Vec2_Up * -30, mFacingRight ? Vec2_Right : -Vec2_Right);
			break;
		}
	}

}