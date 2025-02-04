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

	mLevels[1]->CollidersActive(false);



	mLevels[2] = new Level("lvl3.png", mPlayer);

	mLevels[2]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[2]->AddPlatform(new Platform({ 58 ,Graphics::SCREEN_HEIGHT - 245 }, 200));
	mLevels[2]->AddPlatform(new Platform({Graphics::SCREEN_WIDTH - 58 ,Graphics::SCREEN_HEIGHT - 245 }, 200));
	mLevels[2]->AddPlatform(new Platform({ Graphics::SCREEN_HEIGHT/2 ,Graphics::SCREEN_HEIGHT - 245 }, 150));

	mLevels[2]->AddPlatform(new Platform({ Graphics::SCREEN_HEIGHT / 2 ,Graphics::SCREEN_HEIGHT/2 - 83 }, 390));

	mLevels[2]->AddPlatform(new Platform({ Graphics::SCREEN_HEIGHT / 2 ,73 }, 150));
	mLevels[2]->AddPlatform(new Platform({ 73 ,73 }, 150));
	mLevels[2]->AddPlatform(new Platform({Graphics::SCREEN_WIDTH - 73 ,73 }, 150));

	mLevels[2]->AddWall(new Wall({ 20,Graphics::SCREEN_HEIGHT-85 },160));
	mLevels[2]->AddWall(new Wall({Graphics::SCREEN_WIDTH - 20,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[2]->AddWall(new Wall({ Graphics::SCREEN_WIDTH/2 + 60, Graphics::SCREEN_HEIGHT - 245 }, 150));

	mLevels[2]->AddWall(new Wall({ 20,267 }, 300));
	mLevels[2]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20, 267 }, 300));

	mLevels[2]->AddWall(new Wall({ Graphics::SCREEN_WIDTH / 2 - 60, Graphics::SCREEN_HEIGHT / 2 - 83 }, 150));

	mLevels[2]->CollidersActive(false);



	mLevels[3] = new Level("lvl4.png", mPlayer);

	mLevels[3]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[3]->AddPlatform(new Platform({ 95 ,Graphics::SCREEN_HEIGHT - 210 }, 40));
	mLevels[3]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 95 ,Graphics::SCREEN_HEIGHT - 210 }, 40));

	mLevels[3]->AddPlatform(new Platform({ Graphics::SCREEN_HEIGHT / 2 ,Graphics::SCREEN_HEIGHT - 245 }, 217));
	mLevels[3]->AddPlatform(new Platform({ 0 ,Graphics::SCREEN_HEIGHT - 245 }, 150));
	mLevels[3]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH ,Graphics::SCREEN_HEIGHT - 245 }, 150));

	mLevels[3]->AddPlatform(new Platform({ Graphics::SCREEN_HEIGHT / 2 ,Graphics::SCREEN_HEIGHT / 2 - 83 }, 395));

	mLevels[3]->AddPlatform(new Platform({ Graphics::SCREEN_HEIGHT / 2 ,73 }, 310));

	mLevels[3]->AddWall(new Wall({ 20,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[3]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20,Graphics::SCREEN_HEIGHT - 85 }, 160));

	mLevels[3]->AddWall(new Wall({ 60,Graphics::SCREEN_HEIGHT - 175 }, 70));
	mLevels[3]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 60,Graphics::SCREEN_HEIGHT - 175 }, 70));

	mLevels[3]->AddWall(new Wall({ 20,265 }, 320));
	mLevels[3]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20,265 }, 320));

	mLevels[3]->CollidersActive(false);



	mLevels[4] = new Level("lvl11.png", mPlayer);

	mLevels[4]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[4]->AddPlatform(new Platform({ 170 ,Graphics::SCREEN_HEIGHT - 125 }, 45));
	mLevels[4]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 170 ,Graphics::SCREEN_HEIGHT - 125 }, 45));

	mLevels[4]->AddPlatform(new Platform({ 125 ,Graphics::SCREEN_HEIGHT - 165 }, 45));
	mLevels[4]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 125 ,Graphics::SCREEN_HEIGHT - 165 }, 45));

	mLevels[4]->AddPlatform(new Platform({ 60 ,Graphics::SCREEN_HEIGHT - 245 }, 110));
	mLevels[4]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,Graphics::SCREEN_HEIGHT - 245 }, 110));
	mLevels[4]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 245 }, 140));

	mLevels[4]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,235 }, 150));
	mLevels[4]->AddPlatform(new Platform({ 80 ,235 }, 150));
	mLevels[4]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 80 ,235 }, 150));

	mLevels[4]->AddPlatform(new Platform({ 200 ,77 }, 145));
	mLevels[4]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 200 ,77 }, 145));

	mLevels[4]->AddWall(new Wall({ 100 ,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[4]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 100 ,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[4]->AddWall(new Wall({ 140 ,Graphics::SCREEN_HEIGHT - 85 }, 80));
	mLevels[4]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 140 ,Graphics::SCREEN_HEIGHT - 85 }, 80));
	mLevels[4]->AddWall(new Wall({ 180 ,Graphics::SCREEN_HEIGHT - 85 }, 40));
	mLevels[4]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 180 ,Graphics::SCREEN_HEIGHT - 85 }, 40));

	mLevels[4]->AddWall(new Wall({ 20 ,270 }, 320));
	mLevels[4]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20 ,270 }, 320));

	mLevels[4]->CollidersActive(false);



	mLevels[5] = new Level("lvl8.png", mPlayer);

	mLevels[5]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[5]->AddPlatform(new Platform({ 60 ,Graphics::SCREEN_HEIGHT - 245 }, 250));
	mLevels[5]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,Graphics::SCREEN_HEIGHT - 245 }, 250));

	mLevels[5]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH/2 ,235 }, 300));

	mLevels[5]->AddWall(new Wall({ 20 ,Graphics::SCREEN_HEIGHT - 85 },160));
	mLevels[5]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20 ,Graphics::SCREEN_HEIGHT - 85 },160));
	mLevels[5]->AddWall(new Wall({ 60 ,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[5]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 60 ,Graphics::SCREEN_HEIGHT - 85 }, 160));

	mLevels[5]->AddWall(new Wall({ 20 ,270 }, 320));
	mLevels[5]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20 ,270 }, 320));

	mLevels[5]->CollidersActive(false);



	mLevels[6] = new Level("lvl16.png", mPlayer);

	mLevels[6]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[6]->AddPlatform(new Platform({ 60 ,Graphics::SCREEN_HEIGHT - 245 }, 120));
	mLevels[6]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,Graphics::SCREEN_HEIGHT - 245 }, 120));

	mLevels[6]->AddPlatform(new Platform({ 60 ,235 }, 120));
	mLevels[6]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,235 }, 120));

	mLevels[6]->AddWall(new Wall({ 20 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_HEIGHT));
	mLevels[6]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_HEIGHT));


	mLevels[6]->CollidersActive(false);

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

	if (mLevelIndex > sTotalLevelCount) {// todo temp
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