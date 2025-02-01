#include "Boss.h"

Boss::Boss(Vector2 pos, Player* player) : Enemy(new GLTexture("CarpathianSprites.png",84,17,23,32), player, 10000, 70, false) {

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i] = new Bullet(false);
	}

	mMoving = true;
	mSpeed = 50.0f;

	mFireTime = 0.0f;
	mFireIntervalSingle = 3.0f;
	mFireIntervalRing = 1.5f;

	mFiring = false;
	mFireTexTime = 0.0f;
	mFireTexDur = 0.2f;

	mStateTime = 0.0f;
	mStateDur = 8.0f;
	mAtemptStationaryState = false;

	mFiringTex = new GLTexture("CarpathianSprites.png",58,17,25,32);
	mFiringTex->Scale(Vec2_One*5.0f);
	mFiringTex->Parent(this);

	Position(pos);

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

}

Boss::~Boss() {

	delete mFiringTex;
	mFiringTex = nullptr;

	for (int i = 0; i < MAX_BULLETS; ++i) {
		delete mBullets[i];
		mBullets[i] = nullptr;
	}
}

void Boss::Update() {
	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}

	if (!Active()) {
		return;
	}

	if (!(mAtemptStationaryState && mMoving)) {
		mStateTime += mTimer->DeltaTime();
	}
	
	if (mStateTime >= mStateDur) {
		mAtemptStationaryState = !mAtemptStationaryState;
		mStateTime = 0.0f;
	}


	if (mAtemptStationaryState && abs(Position().x - (Graphics::SCREEN_WIDTH / 2)) < 10.0f) {
		mMoving = false;
	}
	else if (!mAtemptStationaryState) {
		mMoving = true;
	}

	if (mMoving) {
		Translate(-Vec2_Right*mSpeed*mTimer->DeltaTime());

		if (Position().x < -mTexture->ScaledDimensions().x*1.25f) {
			Translate((Vec2_Right * Graphics::SCREEN_WIDTH) + mTexture->ScaledDimensions().x * 1.25f);
		}
	}

	mFireTime += mTimer->DeltaTime();

	if (mFireTime >= (mMoving ? mFireIntervalSingle : mFireIntervalRing)) {

		mMoving ? FireSingle() : FireRing();
		
		mFireTime = 0.0f;
	}

	if (mFiring) {
		mFireTexTime += mTimer->DeltaTime();
		if (mFireTexTime >= mFireTexDur) {
			mFiring = false;
			mFireTexTime = 0.0f;
		}
	}
}

void Boss::Render() {
	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Render();
	}

	if (!Active()) {
		return;
	}
	if (mFiring) {
		mFiringTex->Render();
	}
	else {
		mTexture->Render();
	}

	PhysEntity::Render();
}

void Boss::FireSingle() {
	Vector2 fireDir = (mPlayer->Position() - Position()).Normalized();
	mFiring = true;
	for (int i = 0; i < MAX_BULLETS; ++i) {
		if (!mBullets[i]->Active()) {
			mBullets[i]->Fire(Position() + Vec2_Up * -30, fireDir);
			break;
		}
	}
}

void Boss::FireRing() {
	Vector2 dirs[8] = { {0,1},{1,1},{1,0},{1,-1},{-1,0},{-1,-1},{-1,0},{-1,1} };

	mFiring = true;
	for (int c = 0; c < 8; c++) {
		for (int i = 0; i < MAX_BULLETS; ++i) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Position() + Vec2_Up * -30, dirs[c]);
				break;
			}
		}
	}
}