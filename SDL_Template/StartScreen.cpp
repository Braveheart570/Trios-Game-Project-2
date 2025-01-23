#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	for (int c = 0; c <= 2; c++) {
		mSky[c] = new GLTexture("Sky.png");
		mSky[c]->Scale(Vec2_One*5.0f);
		mSky[c]->Position({110.0f+(c*220.0f),100.0f});
		mSky[c]->Parent(this);
	}

	for (int c = 0; c <= 2; c++) {
		mMountains[c] = new GLTexture("Mountains.png");
		mMountains[c]->Scale(Vec2_One * 5.0f);
		mMountains[c]->Position({ 110.0f + (c * 220.0f),200.0f });
		mMountains[c]->Parent(this);
	}

	mMountains[3] = new GLTexture("MountainsCastle.png");
	mMountains[3]->Scale(Vec2_One * 5.0f);
	mMountains[3]->Position({ 110.0f + (3 * 220.0f),200.0f });
	mMountains[3]->Parent(this);


	mMoon = new GLTexture("Moon.png");
	mMoon->Scale(Vec2_One * 5);
	mMoon->Position({Graphics::SCREEN_WIDTH/2,Graphics::SCREEN_HEIGHT/2});
	mMoon->Parent(this);

	mTitle = new GLTexture("Title.png");
	mTitle->Scale(Vec2_One * 3);
	mTitle->Position({ Graphics::SCREEN_WIDTH / 2,Graphics::SCREEN_HEIGHT / 2 });
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



}

void StartScreen::Render() {
	for (int c = 0; c <= 2; c++) mSky[c]->Render();
	for (int c = 0; c <= 3; c++) mMountains[c]->Render();

	mMoon->Render();
	mTitle->Render();

}