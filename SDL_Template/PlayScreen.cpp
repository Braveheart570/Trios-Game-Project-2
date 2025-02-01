#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mPlayerSpawn = Vector2(Graphics::SCREEN_WIDTH * 0.5f, 570);

	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(mPlayerSpawn);

	mUIBar = new UIBar(mPlayer);
	mUIBar->Parent(this);

	mLevelIndex = 0;

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

	mLevels[0]->AddEnemy(new Bat({ 550,110 }, mPlayer));
	mLevels[0]->AddEnemy(new Bat({ 450,110 }, mPlayer, false));

	mLevels[1] = new Level("lvl2.png", mPlayer);

	mLevels[1]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[1]->AddEnemy(new Fishman({ 500,510 }, mPlayer));
	mLevels[1]->AddEnemy(new Zombie({ 200,100 }, mPlayer));

	mLevels[1]->CollidersActive(false);

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

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N)) {
		NextLevel();
	}

	mLevels[mLevelIndex]->Update();
	mPlayer->Update();
	mUIBar->Update();
}

void PlayScreen::Render() {
	
	mLevels[mLevelIndex]->Render();

	mPlayer->Render();

	mUIBar->Render();

}

void PlayScreen::Reset() {
	//todo call reset functions for player level ui etc...
}

void PlayScreen::NextLevel() {
	mLevels[mLevelIndex]->CollidersActive(false);
	mLevelIndex++;
	mLevels[mLevelIndex]->CollidersActive(true);
	mPlayer->Position(mPlayerSpawn);
}