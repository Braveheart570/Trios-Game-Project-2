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

	mGameOverTex = new GLTexture("GameOver.png");
	mGameOverTex->Parent(this);
	mGameOverTex->Scale(Vec2_One*5.0f);
	mGameOverTex->Position(Graphics::SCREEN_WIDTH/2,Graphics::SCREEN_HEIGHT/2);


	mLevelIndex = 0;

	mLevels[0] = new Level("lvl1.png", mPlayer);
	mLevels[0]->Parent(this);

	mLevels[0]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[0]->AddPlatform(new Platform({ -7 ,Graphics::SCREEN_HEIGHT - 250 }, 240));
	mLevels[0]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH + 7 ,Graphics::SCREEN_HEIGHT - 250 }, 240));

	mLevels[0]->AddPlatform(new Platform({ (Graphics::SCREEN_WIDTH / 2) + 77, Graphics::SCREEN_HEIGHT - 250 }, 70));
	mLevels[0]->AddPlatform(new Platform({ (Graphics::SCREEN_WIDTH / 2) - 80, Graphics::SCREEN_HEIGHT - 250 }, 70));

	mLevels[0]->AddPlatform(new Platform({ (Graphics::SCREEN_WIDTH / 2) + 150, (Graphics::SCREEN_HEIGHT / 2) - 83 }, 80));
	mLevels[0]->AddPlatform(new Platform({ (Graphics::SCREEN_WIDTH / 2) - 150, (Graphics::SCREEN_HEIGHT / 2) - 83 }, 80));

	mLevels[0]->AddPlatform(new Platform({ (Graphics::SCREEN_WIDTH / 2) + 80, 75 }, 75));
	mLevels[0]->AddPlatform(new Platform({ (Graphics::SCREEN_WIDTH / 2) - 80, 75 }, 75));

	mLevels[0]->AddPlatform(new Platform({ (Graphics::SCREEN_WIDTH)-16, 75 }, 200));
	mLevels[0]->AddPlatform(new Platform({ 16, 75 }, 200));

	mLevels[0]->AddWall(new Wall({ 20,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[0]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20,Graphics::SCREEN_HEIGHT - 85 }, 160));

	mLevels[0]->AddWall(new Wall({ 220,Graphics::SCREEN_HEIGHT - 240 }, 320));
	mLevels[0]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 220,Graphics::SCREEN_HEIGHT - 240 }, 320));

	mLevels[0]->AddWall(new Wall({ 20,Graphics::SCREEN_HEIGHT - 380 }, 300));
	mLevels[0]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20,Graphics::SCREEN_HEIGHT - 380 }, 300));

	mLevels[0]->AddEnemy(new Bat({ 550,110 }, mPlayer));
	mLevels[0]->AddEnemy(new Bat({ 450,110 }, mPlayer, false));

	mLevels[0]->AddEnemy(new Torch({500,500},mPlayer));

	mLevels[0]->CollidersActive(true);

	mLevels[1] = new Level("lvl2.png", mPlayer);

	mLevels[1]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[1]->AddPlatform(new Platform({ -83 ,Graphics::SCREEN_HEIGHT - 250 }, 240));
	mLevels[1]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH + 83 ,Graphics::SCREEN_HEIGHT - 250 }, 240));
	mLevels[1]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH/2 ,Graphics::SCREEN_HEIGHT - 250 }, 300));

	mLevels[1]->AddPlatform(new Platform({ 105 ,(Graphics::SCREEN_HEIGHT / 2) - 83 }, 250));
	mLevels[1]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 105 ,(Graphics::SCREEN_HEIGHT / 2) - 83 }, 250));

	mLevels[1]->AddPlatform(new Platform({ 420 ,115 }, 115));
	mLevels[1]->AddPlatform(new Platform({ 220 ,115 }, 115));

	mLevels[1]->AddWall(new Wall({ 20,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[1]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20,Graphics::SCREEN_HEIGHT - 85 }, 160));

	mLevels[1]->AddWall(new Wall({ 20, (Graphics::SCREEN_HEIGHT / 2) - 83 }, 260));
	mLevels[1]->AddWall(new Wall({Graphics::SCREEN_WIDTH - 20, (Graphics::SCREEN_HEIGHT / 2) - 83 }, 260));


	mLevels[1]->AddEnemy(new Fishman({ 500,510 }, mPlayer));
	mLevels[1]->AddEnemy(new Zombie({ 200,100 }, mPlayer));

	mLevels[1]->CollidersActive(false);

	mAudio->PlayMusic("Music/LevelMusic.wav");

}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mUIBar;
	mUIBar = nullptr;

	delete mGameOverTex;
	mGameOverTex = nullptr;

	for (int c = 0; c < sTotalLevelCount; c++) {
		delete mLevels[c];
		mLevels[c] = nullptr;
	}
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

	if (mPlayer->Dead()) mGameOverTex->Render();

}

void PlayScreen::NextLevel() {

	if (mLevelIndex >= 1) {// todo temp
		std::cout << "end of testing levels" << std::endl;
		return;
	}

	mLevels[mLevelIndex]->CollidersActive(false);
	mLevelIndex++;
	mLevels[mLevelIndex]->CollidersActive(true);
	mPlayer->Position(mPlayerSpawn);
}

bool PlayScreen::GameOver() {
	return mPlayer->Dead();
}