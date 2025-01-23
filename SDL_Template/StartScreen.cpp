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
		if (c == 1) {
			mMountains[c] = new GLTexture("MountainsCastle.png");
		}
		else {
			mMountains[c] = new GLTexture("Mountains.png");
		}
		
		mMountains[c]->Scale(Vec2_One * 5.0f);
		mMountains[c]->Position({ (c * 220.0f)-330.0f,300.0f });
		mMountains[c]->Parent(this);
	}


	mMoon = new GLTexture("Moon.png");
	mMoon->Scale(Vec2_One * 5);
	mMoon->Position({Graphics::SCREEN_WIDTH/2,-100.0f});
	mMoon->Parent(this);

	mTitle = new GLTexture("Title.png");
	mTitle->Scale(Vec2_One * 5);
	mTitle->Position({ Graphics::SCREEN_WIDTH / 2,490.0f });
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



}

void StartScreen::Update() {

	float triggerDistance = 110.0f;

	for (auto tex : mMountains) {
		tex->Translate(Vec2_Right*mTimer->DeltaTime()*50.0f);

		if (tex->Position().x >= Graphics::SCREEN_WIDTH + triggerDistance) {
			tex->Translate(-(Vec2_Right*(220.0f*sMountainPannels)));
		}

	}

}

void StartScreen::Render() {
	for (int c = 0; c <= 2; c++) mSky[c]->Render();

	//mMoon->Render();

	for (int c = 0; c < sMountainPannels; c++) mMountains[c]->Render();

	
	//mTitle->Render();

}