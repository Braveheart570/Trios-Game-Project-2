#include "Skeleton.h"

Skeleton::Skeleton(Vector2 pos, Player* player) : Zombie(new AnimatedGLTexture("CarpathianSprites.png",165,0,13,16,2,0.5f, Animation::Layouts::Horizontal),pos,player) {
	mHealth = 4;
	mPts = 300;


	mFireTime = 0.0f;
	mFireInterval = 3.0f;


	for (int i = 0; i < MAX_BONES; ++i) {
		mBones[i] = new Bone();
	}
}

Skeleton::~Skeleton() {
	for (int i = 0; i < MAX_BONES; ++i) {
		delete mBones[i];
		mBones[i] = nullptr;
	}
}

void Skeleton::Update() {
	for (int i = 0; i < MAX_BONES; ++i) {
		mBones[i]->Update();
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

void Skeleton::Render() {
	Zombie::Render();
	for (int i = 0; i < MAX_BONES; ++i) {
		mBones[i]->Render();
	}
}

void Skeleton::Fire() {

	for (int i = 0; i < MAX_BONES; ++i) {
		if (!mBones[i]->Active()) {
			mBones[i]->Fire(Position() + Vec2_Up * -30, Vec2_Up);
			break;
		}
	}

}