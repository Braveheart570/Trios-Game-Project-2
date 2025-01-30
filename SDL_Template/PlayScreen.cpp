#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mUIBar = new UIBar();
	mUIBar->Parent(this);

	mLevels[0] = new Level("lvl1.png", mPlayer);
	mLevels[0]->Parent(this);

}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mUIBar;
	mUIBar = nullptr;
}

void PlayScreen::Update() {
	mLevels[0]->Update();
	mPlayer->Update();
}

void PlayScreen::Render() {
	
	mLevels[0]->Render();

	mPlayer->Render();

	mUIBar->Render();

}

void PlayScreen::Reset() {
	//todo call reset functions for player level ui etc...
}
