#include "ScrollingBG.h"

ScrollingBG::ScrollingBG() {

	mTimer = Timer::Instance();

	for (int c = 0; c <= 2; c++) {
		mSky[c] = new GLTexture("Sky.png");
		mSky[c]->Scale(Vec2_One * 5.0f);
		mSky[c]->Position({ 110.0f + (c * 220.0f),200.0f });
		mSky[c]->Parent(this);
	}

	for (int c = 0; c < sMountainPannels; c++) {
		if (c == 0) {
			mMountains[c] = new GLTexture("MountainsCastle.png");
		}
		else {
			mMountains[c] = new GLTexture("Mountains.png");
		}

		mMountains[c]->Scale(Vec2_One * 5.0f);
		mMountains[c]->Parent(this);

	}


	mMoon = new GLTexture("Moon.png");
	mMoon->Scale(Vec2_One * 5);
	mMoon->Parent(this);

}

ScrollingBG::~ScrollingBG() {

	mTimer = nullptr;

	delete mSky[0];
	mSky[0] = nullptr;
	delete mSky[1];
	mSky[1] = nullptr;
	delete mSky[2];
	mSky[2] = nullptr;

	for (auto tex : mMountains) {
		delete tex;
		tex = nullptr;
	}

}

void ScrollingBG::Update() {
	mMoon->Translate(Vec2_Up * 30.0f * mTimer->DeltaTime());

	float triggerDistance = 110.0f;

	for (int c = 0; c < sMountainPannels; c++) {
		mMountains[c]->Translate(Vec2_Right * mTimer->DeltaTime() * 50.0f);

		if (mMountains[c]->Position().x >= Graphics::SCREEN_WIDTH + triggerDistance) {
			mMountains[c]->Translate(-(Vec2_Right * (220.0f * sMountainPannels)));
			if (c == 0) {
				mMoon->Position({ Graphics::SCREEN_WIDTH / 2,-110.0f });
			}
		}

	}
}

void ScrollingBG::Render() {
	for (int c = 0; c <= 2; c++) mSky[c]->Render();

	if (mMoon->Position().y <= Graphics::SCREEN_HEIGHT - 180) { mMoon->Render(); }

	for (int c = 0; c < sMountainPannels; c++) mMountains[c]->Render();
}

void ScrollingBG::ResetAnimations() {
	

	for (int c = 0; c < sMountainPannels; c++) {
		mMountains[c]->Position({ (c * 220.0f) - 330.0f,300.0f });
	}

	mMoon->Position({ Graphics::SCREEN_WIDTH / 2,-110.0f });
	
}