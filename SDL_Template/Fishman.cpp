#include "Fishman.h"

Fishman::Fishman(Vector2 pos, Player* player) : Enemy(new AnimatedGLTexture("CarpathianSprites.png", 100, 0, 16, 16, 2, 0.75f, Animation::Layouts::Horizontal), player, 400, 3){

	Position(pos);

	nWanderXRight = pos.y + mWanderDist;
	mWanderXLeft = pos.x - mWanderDist;

	mYTrigger = 100;
	mPlayerOriginOffset = -30;

	mFireTime = 0.0f;
	mFireInterval = 2.0f;

	mFacingRight = false;

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i] = new Bullet(false);
	}

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

}

Fishman::~Fishman() {

}

void Fishman::Update() {

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}

	if (!Active()) {
		return;
	}

	mTexture->Update();

	if (mFacingRight) {
		Translate(Vec2_Right * mSpeed * mTimer->DeltaTime());

		if (Position().x >= nWanderXRight) {
			Position(nWanderXRight, Position().y);
			mFacingRight = false;
			mTexture->Flip(false, false);
		}
	}
	else {
		Translate(-Vec2_Right * mSpeed * mTimer->DeltaTime());

		if (Position().x <= mWanderXLeft) {
			Position(mWanderXLeft, Position().y);
			mFacingRight = true;
			mTexture->Flip(true, false);
		}
	}

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
	Enemy::Render();
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