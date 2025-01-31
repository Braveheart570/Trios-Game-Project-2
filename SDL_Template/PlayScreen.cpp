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

	mLevels[0]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[0]->AddPlatform(new Platform({ 60 ,Graphics::SCREEN_HEIGHT - 250 }, 120));
	mLevels[0]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,Graphics::SCREEN_HEIGHT - 250 }, 120));

	mLevels[0]->AddPlatform(new Platform({ (Graphics::SCREEN_WIDTH / 2) + 77, Graphics::SCREEN_HEIGHT - 250 }, 80));
	mLevels[0]->AddPlatform(new Platform({ (Graphics::SCREEN_WIDTH / 2) - 77, Graphics::SCREEN_HEIGHT - 250 }, 80));

	mLevels[0]->AddPlatform(new Platform({ (Graphics::SCREEN_WIDTH / 2) + 150, (Graphics::SCREEN_WIDTH / 2) - 83 }, 100));
	mLevels[0]->AddPlatform(new Platform({ 150, (Graphics::SCREEN_WIDTH / 2) - 83 }, 100));

	mLevels[0]->AddPlatform(new Platform({ (Graphics::SCREEN_WIDTH / 2) + 77, 75 }, 80));
	mLevels[0]->AddPlatform(new Platform({ (Graphics::SCREEN_WIDTH / 2) - 77, 75 }, 80));

	mLevels[0]->AddPlatform(new Platform({ (Graphics::SCREEN_WIDTH)-20, 75 }, 200));
	mLevels[0]->AddPlatform(new Platform({ 20, 75 }, 200));

	mLevels[0]->AddWall(new Wall({ 20,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[0]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20,Graphics::SCREEN_HEIGHT - 85 }, 160));

	mLevels[0]->AddWall(new Wall({ 220,Graphics::SCREEN_HEIGHT - 240 }, 320));
	mLevels[0]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 220,Graphics::SCREEN_HEIGHT - 240 }, 320));

	mLevels[0]->AddWall(new Wall({ 20,Graphics::SCREEN_HEIGHT - 380 }, 300));
	mLevels[0]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20,Graphics::SCREEN_HEIGHT - 380 }, 300));

	mLevels[0]->AddEnemy(new Fishman({ 500,510 }, mPlayer));

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
