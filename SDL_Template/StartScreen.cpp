#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	for (int c = 0; c <= 2; c++) {
		mSky[c] = new GLTexture("Sky.png");
		mSky[c]->Scale(Vec2_One*5.0f);
		mSky[c]->Position({110.0f+(c*220.0f),200.0f});
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

	mTitle = new GLTexture("Title.png");
	mTitle->Scale(Vec2_One * 5);
	mTitle->Parent(this);
	

	// screen animation variables
	ResetAnimation();
}


StartScreen::~StartScreen() {
	mTimer = nullptr;
	mInput = nullptr;

	delete mSky[0];
	mSky[0] = nullptr;
	delete mSky[1];
	mSky[1] = nullptr;
	delete mSky[2];
	mSky[2] = nullptr;

}

void StartScreen::ResetAnimation() {

	for (int c = 0; c < sMountainPannels; c++) {
		mMountains[c]->Position({ (c * 220.0f) - 330.0f,300.0f });
	}

	mMoon->Position({ Graphics::SCREEN_WIDTH / 2,-110.0f });
	mTitle->Position({ Graphics::SCREEN_WIDTH / 2,490.0f });

}

void StartScreen::Update() {

	mMoon->Translate(Vec2_Up * 30.0f * mTimer->DeltaTime());
	
	float triggerDistance = 110.0f;

	for (int c = 0; c < sMountainPannels; c++) {
		mMountains[c]->Translate(Vec2_Right * mTimer->DeltaTime() * 50.0f);

		if (mMountains[c]->Position().x >= Graphics::SCREEN_WIDTH + triggerDistance) {
			mMountains[c]->Translate(-(Vec2_Right*(220.0f*sMountainPannels)));
			if (c==0) {
				mMoon->Position({Graphics::SCREEN_WIDTH/2,-110.0f});
			}
		}

	}

	

}

void StartScreen::Render() {
	for (int c = 0; c <= 2; c++) mSky[c]->Render();

	if (mMoon->Position().y <= Graphics::SCREEN_HEIGHT-180) { mMoon->Render(); }

	for (int c = 0; c < sMountainPannels; c++) mMountains[c]->Render();

	
	mTitle->Render();

}