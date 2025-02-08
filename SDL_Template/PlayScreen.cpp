#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mHeartManager = HeartManager::Instance();

	mPlayerSpawn = Vector2(Graphics::SCREEN_WIDTH * 0.5f, 570);

	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(mPlayerSpawn);

	mUIBar = new UIBar(mPlayer);
	mUIBar->Parent(this);

	mHealthLabelUp = false;
	mHealthUpLabelTime = 0.0f;
	mHealthUpLabelDur = 3.0f;
	mHealthUpgradedlabel = new GLTexture("HEALTH UPGRADED!", "pico-8-mono-upper.ttf", 25, { 255,204,170 });
	mHealthUpgradedlabel->Parent(this);
	mHealthUpgradedlabel->Position(320, 320);


	mGameOverTex = new GLTexture("GameOver.png");
	mGameOverTex->Parent(this);
	mGameOverTex->Scale(Vec2_One*5.0f);
	mGameOverTex->Position(Graphics::SCREEN_WIDTH/2,Graphics::SCREEN_HEIGHT/2);

	mControls = new GLTexture("Controls2.png");
	mControls->Parent(this);
	mControls->Scale(Vec2_One*5.0f);
	mControls->Position(Graphics::SCREEN_WIDTH/2,Graphics::SCREEN_HEIGHT/2);

	mLevelClearedLabel = new GLTexture("Level Cleared", "pico-8-mono-upper.ttf", 25, { 255,204,170 });
	mLevelClearedLabel->Parent(this);
	mLevelClearedLabel->Position(Graphics::SCREEN_WIDTH / 2, 150);

	mLevelCompleted = false;
	LevelTransitionTime = 0.0f;
	LevelTransitionDur = 2.5f;

	mLevelIndex = 0;

	std::string chamberText = "Chamber: " + std::to_string(mLevelIndex + 1);
	MChamberNumLabel = new GLTexture(chamberText, "pico-8-mono-upper.ttf", 25, { 255,204,170 });
	MChamberNumLabel->Parent(this);
	MChamberNumLabel->Position(Graphics::SCREEN_WIDTH / 2, 150);

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

	mLevels[0]->AddEnemy(new Torch({ 80,500 }, mPlayer));
	mLevels[0]->AddEnemy(new Torch({ 560,500 }, mPlayer));

	mLevels[0]->AddEnemy(new Torch({ 245,30 }, mPlayer));
	mLevels[0]->AddEnemy(new Torch({ 395,30 }, mPlayer));

	mLevels[0]->AddEnemy(new Bat({110,310},mPlayer, false));
	mLevels[0]->AddEnemy(new Bat({ 340,310 }, mPlayer));

	mLevels[0]->AddEnemy(new Bat({ 50,140 }, mPlayer, false));
	mLevels[0]->AddEnemy(new Bat({ 390,140 }, mPlayer));

	mLevels[0]->AddEnemy(new Bat({ 450,20 }, mPlayer));

	mLevels[0]->CollidersActive(true);



	mLevels[1] = new Level("lvl2.png", mPlayer);
	mLevels[1]->Parent(this);

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

	mLevels[1]->AddEnemy(new Torch({ 90,500 }, mPlayer));
	mLevels[1]->AddEnemy(new Torch({ 550,500 }, mPlayer));

	mLevels[1]->AddEnemy(new Torch({ 120,380 }, mPlayer));
	mLevels[1]->AddEnemy(new Torch({ 580,380 }, mPlayer));

	mLevels[1]->AddEnemy(new Torch({ 260,55 }, mPlayer));
	mLevels[1]->AddEnemy(new Torch({ 417,55 }, mPlayer));

	mLevels[1]->AddEnemy(new Zombie({ 320,350 }, mPlayer));

	mLevels[1]->AddEnemy(new Zombie({ 130,190 }, mPlayer));
	mLevels[1]->AddEnemy(new Zombie({ 510,190 }, mPlayer));

	mLevels[1]->AddEnemy(new Zombie({ 130,510 }, mPlayer));
	mLevels[1]->AddEnemy(new Zombie({ 510,510 }, mPlayer));

	mLevels[1]->CollidersActive(false);



	mLevels[2] = new Level("lvl3.png", mPlayer);
	mLevels[2]->Parent(this);

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

	mLevels[2]->AddEnemy(new Torch({ 90,500 }, mPlayer));
	mLevels[2]->AddEnemy(new Torch({ 550,500 }, mPlayer));

	mLevels[2]->AddEnemy(new Torch({ 160,340 }, mPlayer));
	mLevels[2]->AddEnemy(new Torch({ 480,340 }, mPlayer));

	mLevels[2]->AddEnemy(new Torch({ 100,200 }, mPlayer));
	mLevels[2]->AddEnemy(new Torch({ 570,200 }, mPlayer));

	mLevels[2]->AddEnemy(new Torch({ 90,30 }, mPlayer));
	mLevels[2]->AddEnemy(new Torch({ 550,30 }, mPlayer));

	mLevels[2]->AddEnemy(new Zombie({ 170,510 }, mPlayer));

	mLevels[2]->AddEnemy(new Zombie({ 40,350 }, mPlayer));
	mLevels[2]->AddEnemy(new Zombie({ 600,350 }, mPlayer));

	mLevels[2]->AddEnemy(new Zombie({ 170,190 }, mPlayer));
	mLevels[2]->AddEnemy(new Zombie({ 440,190 }, mPlayer));

	mLevels[2]->AddEnemy(new Zombie({ 320,40 }, mPlayer));

	mLevels[2]->AddEnemy(new Bat({ 300,300 }, mPlayer, false));

	mLevels[2]->AddEnemy(new Bat({ 415,120 }, mPlayer));

	mLevels[2]->AddEnemy(new Bat({ 430,20 }, mPlayer, false));

	mLevels[2]->CollidersActive(false);



	mLevels[3] = new Level("lvl4.png", mPlayer);
	mLevels[3]->Parent(this);

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

	mLevels[3]->AddEnemy(new Torch({ 160,500 }, mPlayer));
	mLevels[3]->AddEnemy(new Torch({ 480,500 }, mPlayer));

	mLevels[3]->AddEnemy(new Torch({ 80,340 }, mPlayer));
	mLevels[3]->AddEnemy(new Torch({ 560,340 }, mPlayer));

	mLevels[3]->AddEnemy(new Torch({ 80,180 }, mPlayer));
	mLevels[3]->AddEnemy(new Torch({ 560,180 }, mPlayer));

	mLevels[3]->AddEnemy(new Torch({ 80,20 }, mPlayer));
	mLevels[3]->AddEnemy(new Torch({ 560,20 }, mPlayer));

	mLevels[3]->AddEnemy(new Fishman({ 320,350 }, mPlayer));

	mLevels[3]->AddEnemy(new Fishman({ 290,190 }, mPlayer));
	mLevels[3]->AddEnemy(new Fishman({ 450,190 }, mPlayer));

	mLevels[3]->AddEnemy(new Fishman({ 320,30 }, mPlayer));

	mLevels[3]->AddEnemy(new Bat({ 140,300 }, mPlayer, false));
	mLevels[3]->AddEnemy(new Bat({ 500,300 }, mPlayer));

	mLevels[3]->AddEnemy(new Bat({ 300,120 }, mPlayer));

	mLevels[3]->CollidersActive(false);



	mLevels[4] = new Level("lvl5.png", mPlayer);
	mLevels[4]->Parent(this);

	mLevels[4]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[4]->AddPlatform(new Platform({ 320 ,435 }, 120));

	mLevels[4]->AddPlatform(new Platform({ 60 ,395 }, 190));
	mLevels[4]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,395 }, 190));

	mLevels[4]->AddPlatform(new Platform({ 320 ,275 }, 120));

	mLevels[4]->AddPlatform(new Platform({ 60 ,235 }, 190));
	mLevels[4]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,235 }, 190));

	mLevels[4]->AddPlatform(new Platform({ 320 ,115 }, 120));

	mLevels[4]->AddPlatform(new Platform({ 60 ,75 }, 190));
	mLevels[4]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,75 }, 190));

	mLevels[4]->AddWall(new Wall({ 20 ,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[4]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20 ,Graphics::SCREEN_HEIGHT - 85 }, 160));

	mLevels[4]->AddWall(new Wall({ 20 ,235 }, 320));
	mLevels[4]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20 ,235 }, 320));

	mLevels[4]->AddEnemy(new Torch({ 400,500 }, mPlayer));
	mLevels[4]->AddEnemy(new Torch({ 240,500 }, mPlayer));

	mLevels[4]->AddEnemy(new Torch({ 360,370 }, mPlayer));

	mLevels[4]->AddEnemy(new Torch({ 90,160 }, mPlayer));

	mLevels[4]->AddEnemy(new Torch({ 360,60 }, mPlayer));

	mLevels[4]->AddEnemy(new Torch({ 550,20 }, mPlayer));

	mLevels[4]->AddEnemy(new Zombie({ 120,510 }, mPlayer));
	mLevels[4]->AddEnemy(new Zombie({ 520,510 }, mPlayer));

	mLevels[4]->AddEnemy(new Pumpkin({ 90,360 }, mPlayer));

	mLevels[4]->AddEnemy(new Pumpkin({ 550,200 }, mPlayer));

	mLevels[4]->AddEnemy(new Pumpkin({ 90,40 }, mPlayer));

	mLevels[4]->AddEnemy(new Bat({ 520,300 }, mPlayer));

	mLevels[4]->AddEnemy(new Bat({ 140,150 }, mPlayer, false));

	mLevels[4]->AddEnemy(new Bat({ 480,40 }, mPlayer));


	mLevels[4]->CollidersActive(false);



	mLevels[5] = new Level("lvl6.png", mPlayer);
	mLevels[5]->Parent(this);

	mLevels[5]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[5]->AddPlatform(new Platform({ 60 ,517 }, 190));
	mLevels[5]->AddPlatform(new Platform({ 580 ,517 }, 190));

	mLevels[5]->AddPlatform(new Platform({ -60 ,397 }, 190));
	mLevels[5]->AddPlatform(new Platform({ 700 ,397 }, 190));
	mLevels[5]->AddPlatform(new Platform({ 320 ,397 }, 230));

	mLevels[5]->AddPlatform(new Platform({ 60 ,235 }, 190));
	mLevels[5]->AddPlatform(new Platform({ 580 ,235 }, 190));
	mLevels[5]->AddPlatform(new Platform({ 320 ,235 }, 130));

	mLevels[5]->AddWall(new Wall({ 17 ,Graphics::SCREEN_HEIGHT - 85 }, 150));
	mLevels[5]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 17 ,Graphics::SCREEN_HEIGHT - 85 }, 150));

	mLevels[5]->AddWall(new Wall({ 140 ,Graphics::SCREEN_HEIGHT - 85 }, 30));
	mLevels[5]->AddWall(new Wall({ 500 ,Graphics::SCREEN_HEIGHT - 85 }, 30));

	mLevels[5]->AddWall(new Wall({ 17 ,240 }, 250));
	mLevels[5]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 17 ,240 }, 250));

	mLevels[5]->AddEnemy(new Torch({ 140,490 }, mPlayer));
	mLevels[5]->AddEnemy(new Torch({ 500,490 }, mPlayer));

	mLevels[5]->AddEnemy(new Fishman({ 210,510 }, mPlayer));
	mLevels[5]->AddEnemy(new Fishman({ 580,480 }, mPlayer));

	mLevels[5]->AddEnemy(new Torch({ 320,340 }, mPlayer));

	mLevels[5]->AddEnemy(new Skeleton({ 260,350 }, mPlayer));
	mLevels[5]->AddEnemy(new Skeleton({ 380,350 }, mPlayer));

	mLevels[5]->AddEnemy(new Bat({ 120,290 }, mPlayer));

	mLevels[5]->AddEnemy(new Fishman({ 60,190 }, mPlayer));
	mLevels[5]->AddEnemy(new Fishman({ 580,190 }, mPlayer));

	mLevels[5]->AddEnemy(new Bat({ 200,130 }, mPlayer, false));
	mLevels[5]->AddEnemy(new Bat({ 440,130 }, mPlayer));

	mLevels[5]->AddEnemy(new Bat({ 100,10 }, mPlayer, false));
	mLevels[5]->AddEnemy(new Bat({ 380,10 }, mPlayer, false));
	mLevels[5]->AddEnemy(new Bat({ 550,10 }, mPlayer));

	mLevels[5]->CollidersActive(false);




	mLevels[6] = new Level("lvl7.png", mPlayer);
	mLevels[6]->Parent(this);

	mLevels[6]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[6]->AddPlatform(new Platform({ 170 ,395 }, 600));
	mLevels[6]->AddPlatform(new Platform({ 640 ,395 }, 80));

	mLevels[6]->AddPlatform(new Platform({ 470 ,235 }, 600));

	mLevels[6]->AddPlatform(new Platform({ 170 ,75 }, 600));

	mLevels[6]->AddWall(new Wall({ 17 ,Graphics::SCREEN_HEIGHT - 85 }, 150));
	mLevels[6]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 17 ,Graphics::SCREEN_HEIGHT - 85 }, 150));

	mLevels[6]->AddWall(new Wall({ 17 ,270 }, 320));
	mLevels[6]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 17 ,270 }, 320));

	mLevels[6]->AddEnemy(new Torch({ 160,490 }, mPlayer));
	mLevels[6]->AddEnemy(new Torch({ 480,490 }, mPlayer));

	mLevels[6]->AddEnemy(new Torch({ 210,310 }, mPlayer));
	mLevels[6]->AddEnemy(new Torch({ 430,310 }, mPlayer));

	mLevels[6]->AddEnemy(new Torch({ 160,170 }, mPlayer));
	mLevels[6]->AddEnemy(new Torch({ 480,170 }, mPlayer));

	mLevels[6]->AddEnemy(new Torch({ 210,30 }, mPlayer));
	mLevels[6]->AddEnemy(new Torch({ 430,30 }, mPlayer));

	mLevels[6]->AddEnemy(new Zombie({ 130,510 }, mPlayer));

	mLevels[6]->AddEnemy(new Zombie({ 400,350 }, mPlayer));

	mLevels[6]->AddEnemy(new Zombie({ 400,190 }, mPlayer));

	mLevels[6]->AddEnemy(new Zombie({ 400,30 }, mPlayer));

	mLevels[6]->AddEnemy(new Skeleton({ 130,350 }, mPlayer));

	mLevels[6]->AddEnemy(new Skeleton({ 590,190 }, mPlayer));

	mLevels[6]->AddEnemy(new Skeleton({ 170,30 }, mPlayer));

	mLevels[6]->AddEnemy(new Bat({ 550,460 }, mPlayer));

	mLevels[6]->AddEnemy(new Bat({ 70,150 }, mPlayer, false));

	mLevels[6]->AddEnemy(new Bat({ 550,10 }, mPlayer));

	mLevels[6]->CollidersActive(false);



	mLevels[7] = new Level("lvl8.png", mPlayer);
	mLevels[7]->Parent(this);

	mLevels[7]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[7]->AddPlatform(new Platform({ 60 ,Graphics::SCREEN_HEIGHT - 245 }, 250));
	mLevels[7]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,Graphics::SCREEN_HEIGHT - 245 }, 250));

	mLevels[7]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,235 }, 300));

	mLevels[7]->AddWall(new Wall({ 20 ,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[7]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20 ,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[7]->AddWall(new Wall({ 60 ,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[7]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 60 ,Graphics::SCREEN_HEIGHT - 85 }, 160));

	mLevels[7]->AddWall(new Wall({ 20 ,270 }, 320));
	mLevels[7]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20 ,270 }, 320));

	mLevels[7]->AddEnemy(new Torch({ 100,500 }, mPlayer));
	mLevels[7]->AddEnemy(new Torch({ 540,500 }, mPlayer));

	mLevels[7]->AddEnemy(new Torch({ 100,150 }, mPlayer));
	mLevels[7]->AddEnemy(new Torch({ 540,150 }, mPlayer));

	mLevels[7]->AddEnemy(new Mummy({ 450,490 }, mPlayer));

	mLevels[7]->AddEnemy(new Mummy({ 70,330 }, mPlayer));

	mLevels[7]->AddEnemy(new Mummy({ 320,170 }, mPlayer));

	mLevels[7]->CollidersActive(false);



	mLevels[8] = new Level("Lvl9.png", mPlayer);
	mLevels[8]->Parent(this);

	mLevels[8]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[8]->AddPlatform(new Platform({ 60 ,Graphics::SCREEN_HEIGHT - 245 }, 180));
	mLevels[8]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,Graphics::SCREEN_HEIGHT - 245 }, 180));
	mLevels[8]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH/2 ,Graphics::SCREEN_HEIGHT - 245 }, 150));

	mLevels[8]->AddPlatform(new Platform({ 60 ,235 }, 180));
	mLevels[8]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,235 }, 180));
	mLevels[8]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,235 }, 150));

	mLevels[8]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,115 }, 290));

	mLevels[8]->AddWall(new Wall({ 100 ,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[8]->AddWall(new Wall({ 540 ,Graphics::SCREEN_HEIGHT - 85 }, 160));

	mLevels[8]->AddWall(new Wall({ 20 ,230 }, 250));
	mLevels[8]->AddWall(new Wall({ 620 ,230 }, 250));

	mLevels[8]->AddEnemy(new Torch({ 400,500 }, mPlayer));
	mLevels[8]->AddEnemy(new Torch({ 240,500 }, mPlayer));

	mLevels[8]->AddEnemy(new Torch({ 400,330 }, mPlayer));
	mLevels[8]->AddEnemy(new Torch({ 240,330 }, mPlayer));
	mLevels[8]->AddEnemy(new Torch({ 80,330 }, mPlayer));
	mLevels[8]->AddEnemy(new Torch({ 560,330 }, mPlayer));

	mLevels[8]->AddEnemy(new Torch({ 430,50 }, mPlayer));
	mLevels[8]->AddEnemy(new Torch({ 270,50 }, mPlayer));

	mLevels[8]->AddEnemy(new RedBat({ 480,480 }, mPlayer));

	mLevels[8]->AddEnemy(new RedBat({ 580,35 }, mPlayer));

	mLevels[8]->AddEnemy(new Pumpkin({ 320,360 }, mPlayer));

	mLevels[8]->AddEnemy(new Witch({ 320,200 }, mPlayer));

	mLevels[8]->AddEnemy(new Zombie({ 80,190 }, mPlayer));
	mLevels[8]->AddEnemy(new Zombie({ 560,190 }, mPlayer));

	mLevels[8]->CollidersActive(false);



	mLevels[9] = new Level("Lvl10.png", mPlayer);
	mLevels[9]->Parent(this);

	mLevels[9]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[9]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 205 }, 150));

	mLevels[9]->AddPlatform(new Platform({ -30 ,Graphics::SCREEN_HEIGHT - 245 }, 360));
	mLevels[9]->AddPlatform(new Platform({ 670 ,Graphics::SCREEN_HEIGHT - 245 }, 360));

	mLevels[9]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,275}, 150));

	mLevels[9]->AddPlatform(new Platform({ 60 ,235 }, 180));
	mLevels[9]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,235 }, 180));

	mLevels[9]->AddPlatform(new Platform({ 220 ,115 }, 110));
	mLevels[9]->AddPlatform(new Platform({ 420 ,115 }, 110));

	mLevels[9]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,75 }, 150));

	mLevels[9]->AddWall(new Wall({ 20 ,235 }, 300));
	mLevels[9]->AddWall(new Wall({ 620 ,235 }, 300));

	mLevels[9]->AddWall(new Wall({ 263 ,115 }, 35));
	mLevels[9]->AddWall(new Wall({ 373 ,115 }, 35));

	mLevels[9]->AddEnemy(new Torch({ 230,350 }, mPlayer));
	mLevels[9]->AddEnemy(new Torch({ 410,350 }, mPlayer));

	mLevels[9]->AddEnemy(new Torch({ 230,30 }, mPlayer));
	mLevels[9]->AddEnemy(new Torch({ 410,30 }, mPlayer));

	mLevels[9]->AddEnemy(new Zombie({ 100,510 }, mPlayer));
	mLevels[9]->AddEnemy(new Zombie({ 540,510 }, mPlayer));

	mLevels[9]->AddEnemy(new Zombie({ 570,350 }, mPlayer));

	mLevels[9]->AddEnemy(new Skeleton({ 570,200 }, mPlayer));

	mLevels[9]->AddEnemy(new Pumpkin({ 70,200 }, mPlayer));

	mLevels[9]->AddEnemy(new Witch({ 320,40 }, mPlayer));

	mLevels[9]->CollidersActive(false);



	mLevels[10] = new Level("lvl11.png", mPlayer);
	mLevels[10]->Parent(this);

	mLevels[10]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[10]->AddPlatform(new Platform({ 170 ,Graphics::SCREEN_HEIGHT - 125 }, 45));
	mLevels[10]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 170 ,Graphics::SCREEN_HEIGHT - 125 }, 45));

	mLevels[10]->AddPlatform(new Platform({ 125 ,Graphics::SCREEN_HEIGHT - 165 }, 45));
	mLevels[10]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 125 ,Graphics::SCREEN_HEIGHT - 165 }, 45));

	mLevels[10]->AddPlatform(new Platform({ 60 ,Graphics::SCREEN_HEIGHT - 245 }, 110));
	mLevels[10]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,Graphics::SCREEN_HEIGHT - 245 }, 110));
	mLevels[10]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 245 }, 140));

	mLevels[10]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,235 }, 150));
	mLevels[10]->AddPlatform(new Platform({ 80 ,235 }, 150));
	mLevels[10]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 80 ,235 }, 150));

	mLevels[10]->AddPlatform(new Platform({ 200 ,77 }, 145));
	mLevels[10]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 200 ,77 }, 145));

	mLevels[10]->AddWall(new Wall({ 100 ,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[10]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 100 ,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mLevels[10]->AddWall(new Wall({ 140 ,Graphics::SCREEN_HEIGHT - 85 }, 80));
	mLevels[10]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 140 ,Graphics::SCREEN_HEIGHT - 85 }, 80));
	mLevels[10]->AddWall(new Wall({ 180 ,Graphics::SCREEN_HEIGHT - 85 }, 40));
	mLevels[10]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 180 ,Graphics::SCREEN_HEIGHT - 85 }, 40));

	mLevels[10]->AddWall(new Wall({ 20 ,270 }, 320));
	mLevels[10]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20 ,270 }, 320));

	mLevels[10]->AddEnemy(new RedBat({ 530,460 }, mPlayer));

	mLevels[10]->AddEnemy(new Zombie({ 40,350 }, mPlayer));
	mLevels[10]->AddEnemy(new Zombie({ 600,350 }, mPlayer));

	mLevels[10]->AddEnemy(new Pumpkin({ 320,200 }, mPlayer));

	mLevels[10]->AddEnemy(new Skeleton({ 90,190 }, mPlayer));
	mLevels[10]->AddEnemy(new Skeleton({ 550,190 }, mPlayer));

	mLevels[10]->AddEnemy(new Witch({ 210,40 }, mPlayer));
	mLevels[10]->AddEnemy(new Witch({ 430,40 }, mPlayer));

	mLevels[10]->CollidersActive(false);



	mLevels[11] = new Level("lvl12.png", mPlayer);

	mLevels[11]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[11]->AddPlatform(new Platform({ 5 ,395 }, 200));
	mLevels[11]->AddPlatform(new Platform({ 635 ,395 }, 200));
	mLevels[11]->AddPlatform(new Platform({ 240 ,395 }, 70));
	mLevels[11]->AddPlatform(new Platform({ 400 ,395 }, 70));

	mLevels[11]->AddPlatform(new Platform({ 320 ,235 }, 220));

	mLevels[11]->AddPlatform(new Platform({ 5 ,155 }, 200));
	mLevels[11]->AddPlatform(new Platform({ 635 ,155 }, 200));

	mLevels[11]->AddPlatform(new Platform({ 320 ,75 }, 220));

	mLevels[11]->AddWall(new Wall({ 17 ,Graphics::SCREEN_HEIGHT - 85 }, 150));
	mLevels[11]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 17 ,Graphics::SCREEN_HEIGHT - 85 }, 150));
	mLevels[11]->AddWall(new Wall({ 220 ,Graphics::SCREEN_HEIGHT - 85 }, 150));
	mLevels[11]->AddWall(new Wall({ 420 ,Graphics::SCREEN_HEIGHT - 85 }, 150));

	mLevels[11]->AddWall(new Wall({ 17 ,270 }, 320));
	mLevels[11]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 17 ,270 }, 320));

	mLevels[11]->AddEnemy(new Torch({ 240,330 }, mPlayer));
	mLevels[11]->AddEnemy(new Torch({ 400,330 }, mPlayer));

	mLevels[11]->AddEnemy(new Torch({ 100,30 }, mPlayer));
	mLevels[11]->AddEnemy(new Torch({ 540,30 }, mPlayer));

	mLevels[11]->AddEnemy(new Pumpkin({ 80,520 }, mPlayer));

	mLevels[11]->AddEnemy(new Pumpkin({ 600,360 }, mPlayer));

	mLevels[11]->AddEnemy(new Pumpkin({ 230,200 }, mPlayer));

	mLevels[11]->AddEnemy(new Pumpkin({ 410,40 }, mPlayer));

	mLevels[11]->AddEnemy(new Fishman({ 560,510 }, mPlayer));

	mLevels[11]->AddEnemy(new Fishman({ 410,190 }, mPlayer));

	mLevels[11]->AddEnemy(new Fishman({ 300,40 }, mPlayer));

	mLevels[11]->AddEnemy(new RedBat({ 140,310 }, mPlayer));

	mLevels[11]->AddEnemy(new RedBat({ 470,10 }, mPlayer));

	mLevels[11]->CollidersActive(false);



	mLevels[12] = new Level("lvl13.png", mPlayer);
	mLevels[12]->Parent(this);
	
	mLevels[12]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[12]->AddPlatform(new Platform({ 80 ,395 }, 300));
	mLevels[12]->AddPlatform(new Platform({ 560 ,395 }, 300));

	mLevels[12]->AddPlatform(new Platform({ 0 ,235 }, 150));
	mLevels[12]->AddPlatform(new Platform({ 640 ,235 }, 150));
	mLevels[12]->AddPlatform(new Platform({ 320 ,235 }, 225));

	mLevels[12]->AddPlatform(new Platform({ 100 ,75 }, 250));
	mLevels[12]->AddPlatform(new Platform({ 540 ,75 }, 250));

	mLevels[12]->AddWall(new Wall({ 17 ,Graphics::SCREEN_HEIGHT - 85 }, 150));
	mLevels[12]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 17 ,Graphics::SCREEN_HEIGHT - 85 }, 150));

	mLevels[12]->AddWall(new Wall({ 17 ,250 }, 320));
	mLevels[12]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 17 ,250 }, 320));

	mLevels[12]->AddEnemy(new Torch({ 430,510 }, mPlayer));
	mLevels[12]->AddEnemy(new Torch({ 210,510 }, mPlayer));

	mLevels[12]->AddEnemy(new Torch({ 560,480 }, mPlayer));

	mLevels[12]->AddEnemy(new Torch({ 40,360 }, mPlayer));
	mLevels[12]->AddEnemy(new Torch({ 600,360 }, mPlayer));

	mLevels[12]->AddEnemy(new Torch({ 410,200 }, mPlayer));
	mLevels[12]->AddEnemy(new Torch({ 230,200 }, mPlayer));

	mLevels[12]->AddEnemy(new Torch({ 560,50 }, mPlayer));

	mLevels[12]->AddEnemy(new Zombie({ 140,510 }, mPlayer));
	mLevels[12]->AddEnemy(new Zombie({ 490,510 }, mPlayer));

	mLevels[12]->AddEnemy(new Zombie({ 340,190 }, mPlayer));

	mLevels[12]->AddEnemy(new Skeleton({ 130,350 }, mPlayer));
	mLevels[12]->AddEnemy(new Skeleton({ 510,350 }, mPlayer));

	mLevels[12]->AddEnemy(new Skeleton({ 160,30 }, mPlayer));
	mLevels[12]->AddEnemy(new Skeleton({ 480,30 }, mPlayer));

	mLevels[12]->AddEnemy(new Pumpkin({ 60,40 }, mPlayer));

	mLevels[12]->CollidersActive(false);



	mLevels[13] = new Level("lvl14.png", mPlayer);
	mLevels[13]->Parent(this);

	mLevels[13]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[13]->AddPlatform(new Platform({ 60 ,Graphics::SCREEN_HEIGHT - 245 }, 245));
	mLevels[13]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,Graphics::SCREEN_HEIGHT - 245 }, 245));

	mLevels[13]->AddPlatform(new Platform({ 320 ,235 }, 290));

	mLevels[13]->AddPlatform(new Platform({ 320 ,75 }, 230));

	mLevels[13]->AddWall(new Wall({ 17 ,Graphics::SCREEN_HEIGHT - 85 }, 150));
	mLevels[13]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 17 ,Graphics::SCREEN_HEIGHT - 85 }, 150));

	mLevels[13]->AddWall(new Wall({ 180 ,Graphics::SCREEN_HEIGHT - 85 }, 150));
	mLevels[13]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 180 ,Graphics::SCREEN_HEIGHT - 85 }, 150));

	mLevels[13]->AddWall(new Wall({ 17 ,260 }, 320));
	mLevels[13]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 17 ,260 }, 320));

	mLevels[13]->AddEnemy(new Torch({ 250,320 }, mPlayer));
	mLevels[13]->AddEnemy(new Torch({ 390,320 }, mPlayer));

	mLevels[13]->AddEnemy(new Torch({ 250,40 }, mPlayer));
	mLevels[13]->AddEnemy(new Torch({ 390,40 }, mPlayer));

	mLevels[13]->AddEnemy(new Witch({ 100,355 }, mPlayer));
	mLevels[13]->AddEnemy(new Witch({ 540,355 }, mPlayer));

	mLevels[13]->AddEnemy(new Witch({ 320,40 }, mPlayer));

	mLevels[13]->AddEnemy(new RedBat({ 100,470 }, mPlayer));
	mLevels[13]->AddEnemy(new RedBat({ 540,470 }, mPlayer));

	mLevels[13]->AddEnemy(new RedBat({ 60,180 }, mPlayer, false));
	mLevels[13]->AddEnemy(new RedBat({ 500,180 }, mPlayer));

	mLevels[13]->AddEnemy(new RedBat({ 100,30 }, mPlayer, false));
	mLevels[13]->AddEnemy(new RedBat({ 540,30 }, mPlayer, false));

	mLevels[13]->CollidersActive(false);



	mLevels[14] = new Level("lvl15.png", mPlayer);
	mLevels[14]->Parent(this);

	mLevels[14]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[14]->AddPlatform(new Platform({ 0 ,Graphics::SCREEN_HEIGHT - 245 }, 200));
	mLevels[14]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH ,Graphics::SCREEN_HEIGHT - 245 }, 200));
	mLevels[14]->AddPlatform(new Platform({ 320 ,Graphics::SCREEN_HEIGHT - 245 }, 140));

	mLevels[14]->AddPlatform(new Platform({ 0 ,235 }, 300));
	mLevels[14]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH ,235 }, 300));

	mLevels[14]->AddPlatform(new Platform({ 0 ,75 }, 300));
	mLevels[14]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH ,75 }, 300));
	mLevels[14]->AddPlatform(new Platform({ 320 ,75 }, 140));

	mLevels[14]->AddWall(new Wall({ 17 ,Graphics::SCREEN_HEIGHT - 85 }, 150));
	mLevels[14]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 17 ,Graphics::SCREEN_HEIGHT - 85 }, 150));

	mLevels[14]->AddWall(new Wall({ 100 ,Graphics::SCREEN_HEIGHT - 245 }, 150));
	mLevels[14]->AddWall(new Wall({ 540 ,Graphics::SCREEN_HEIGHT - 245 }, 150));

	mLevels[14]->AddWall(new Wall({ 17 ,235 }, 320));
	mLevels[14]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 17 ,235 }, 320));

	mLevels[14]->AddEnemy(new Torch({ 180,330 }, mPlayer));
	mLevels[14]->AddEnemy(new Torch({ 460,330 }, mPlayer));

	mLevels[14]->AddEnemy(new Witch({ 80,520 }, mPlayer));
	mLevels[14]->AddEnemy(new Witch({ 560,520 }, mPlayer));

	mLevels[14]->AddEnemy(new Witch({ 320,40 }, mPlayer));

	mLevels[14]->AddEnemy(new Pumpkin({ 320,360 }, mPlayer));

	mLevels[14]->AddEnemy(new Zombie({ 100,200 }, mPlayer));
	mLevels[14]->AddEnemy(new Zombie({ 540,200 }, mPlayer));

	mLevels[14]->AddEnemy(new Skeleton({ 100,30 }, mPlayer));
	mLevels[14]->AddEnemy(new Skeleton({ 540,30 }, mPlayer));

	mLevels[14]->AddEnemy(new RedBat({ 140,140 }, mPlayer, false));

	mLevels[14]->AddEnemy(new RedBat({ 450,10 }, mPlayer));

	mLevels[14]->CollidersActive(false);



	mLevels[sTotalLevelCount - 1] = new Level("lvl16.png", mPlayer);
	mLevels[sTotalLevelCount - 1]->Parent(this);

	mLevels[sTotalLevelCount - 1]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_WIDTH + 400));

	mLevels[sTotalLevelCount - 1]->AddPlatform(new Platform({ 60 ,Graphics::SCREEN_HEIGHT - 245 }, 120));
	mLevels[sTotalLevelCount - 1]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,Graphics::SCREEN_HEIGHT - 245 }, 120));

	mLevels[sTotalLevelCount - 1]->AddPlatform(new Platform({ 60 ,235 }, 120));
	mLevels[sTotalLevelCount - 1]->AddPlatform(new Platform({ Graphics::SCREEN_WIDTH - 60 ,235 }, 120));

	mLevels[sTotalLevelCount - 1]->AddWall(new Wall({ 20 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_HEIGHT));
	mLevels[sTotalLevelCount - 1]->AddWall(new Wall({ Graphics::SCREEN_WIDTH - 20 ,Graphics::SCREEN_HEIGHT - 85 }, Graphics::SCREEN_HEIGHT));

	mLevels[sTotalLevelCount - 1]->AddEnemy(new Boss({ 450,260 }, mPlayer));

	mLevels[sTotalLevelCount - 1]->CollidersActive(false);

	mAudio->PlayMusic("Music/LevelMusic.wav");

	mStarted = false;
	mIntroTime = 0.0f;
	mIntroDur = 4.0f;

}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	mHeartManager->Release();
	mHeartManager = nullptr;

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

	delete MChamberNumLabel;
	MChamberNumLabel = nullptr;

	delete mControls;
	mControls = nullptr;
}

void PlayScreen::Update() {

	if (mStarted) {
		
		if (mLevelCompleted) {
			LevelTransitionTime += mTimer->DeltaTime();
			if (LevelTransitionTime >= LevelTransitionDur) {
				NextLevel();
			}
		}
		else if (mLevels[mLevelIndex]->LevelComplete()) {
			mLevelCompleted = true;
		}

		mLevels[mLevelIndex]->Update();
		mPlayer->Update();
		mUIBar->Update();
		mHeartManager->Update();

		if (mHealthLabelUp) {
			mHealthUpLabelTime += mTimer->DeltaTime();
			if (mHealthUpLabelTime >= mHealthUpLabelDur) {
				mHealthLabelUp = false;
				mHealthUpLabelTime = 0.0f;
			}
		}


	}
	else {
		mIntroTime += mTimer->DeltaTime();
		if (mIntroTime >= mIntroDur) {
			mStarted = true;
		}
	}
}

void PlayScreen::Render() {
	
	mLevels[mLevelIndex]->Render();

	mPlayer->Render();

	mUIBar->Render();

	mHeartManager->Render();

	if (mPlayer->Dead()) mGameOverTex->Render();

	if (!mStarted) {
		if (mLevelIndex == 0) {
			mControls->Render();
		}
		MChamberNumLabel->Render();
	}

	if (mLevelCompleted) {
		mLevelClearedLabel->Render();
	}

	if (mHealthLabelUp) mHealthUpgradedlabel->Render();

}

void PlayScreen::NextLevel() {

	if (mLevelIndex == sTotalLevelCount-1) {
		mWin = true;
		return;
	}

	mLevels[mLevelIndex]->CollidersActive(false);
	mLevelIndex++;
	mLevels[mLevelIndex]->CollidersActive(true);
	mPlayer->Position(mPlayerSpawn);

	if (mLevelIndex == 7) {
		mPlayer->UpgradeHealth();
		mHealthLabelUp = true;
	}

	mHeartManager->ClearHearts();

	mIntroDur = 2.5f;
	mIntroTime = 0.0f;
	mStarted = false;

	delete MChamberNumLabel;
	std::string chamberText = "Chamber: " + std::to_string(mLevelIndex + 1);
	MChamberNumLabel = new GLTexture(chamberText, "pico-8-mono-upper.ttf", 20, { 255,204,170 });
	MChamberNumLabel->Parent(this);
	MChamberNumLabel->Position(Graphics::SCREEN_WIDTH / 2, 150);

	mLevelCompleted = false;
	LevelTransitionTime = 0.0f;
}

bool PlayScreen::GameOver() {
	return mPlayer->Dead();
}

bool PlayScreen::Win() {
	return mWin;
}