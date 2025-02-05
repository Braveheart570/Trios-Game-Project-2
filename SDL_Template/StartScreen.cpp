#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mBackground = new ScrollingBG();
	mBackground->Parent(this);

	mTitle = new GLTexture("Title.png");
	mTitle->Scale(Vec2_One * 5);
	mTitle->Parent(this);
	

	// screen animation variables
	ResetAnimation();
}


StartScreen::~StartScreen() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mBackground;
	mBackground = nullptr;

}

void StartScreen::ResetAnimation() {
	mAudio->PlayMusic("Music/menuMusic.wav");
	mBackground->ResetAnimations();
	mTitle->Position({ Graphics::SCREEN_WIDTH / 2,490.0f });

}

void StartScreen::Update() {

	
	mBackground->Update();
	

}

void StartScreen::Render() {
	

	mBackground->Render();
	mTitle->Render();

}