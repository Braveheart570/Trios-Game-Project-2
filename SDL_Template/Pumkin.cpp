#include "Pumpkin.h"

Pumpkin::Pumpkin(Vector2 pos, Player* player) : Enemy(new GLTexture("CarpathianSprites.png",163,18,13,13),player,600,5,false) {

	mFiringTex = new GLTexture("CarpathianSprites.png", 178, 18, 13, 13);
	mFiringTex->Scale(Vec2_One * 5.0f);
	mFiringTex->Parent(this);

	Position(pos);

	mYTrigger = 100;
	mPlayerOriginOffset = -30;

	mFireTime = 0.0f;
	mFireInterval = 2.0f;

	mFiring = false;
	mFireTexTime = 0.0f;
	mFireTexDur = 0.15f;

	mFacingRight = false;

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i] = new Bullet(false);
	}

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

}

Pumpkin::~Pumpkin() {
	delete mFiringTex;
	mFiringTex = nullptr;
}

void Pumpkin::Update() {
	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}

	if (!Active()) {
		return;
	}

	if (mPlayer->Position().x > Position().x) {
		mFacingRight = true;
	}
	else {
		mFacingRight = false;
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

	if (mFiring) {
		mFireTexTime += mTimer->DeltaTime();
		if (mFireTexTime >= mFireTexDur) {
			mFiring = false;
			mFireTexTime = 0.0f;
		}
	}

}

void Pumpkin::Fire() {
	mFiring = true;
	for (int i = 0; i < MAX_BULLETS; ++i) {
		if (!mBullets[i]->Active()) {
			mBullets[i]->Fire(Position() + Vec2_Up * -30, mFacingRight);
			break;
		}
	}
}

void Pumpkin::Render() {

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


	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Render();
	}

}