#include "level.h"

Level::Level(std::string texture, Player* player) {
	mLevelTexture = new GLTexture(texture);
	mLevelTexture->Position({ Graphics::SCREEN_WIDTH / 2,(Graphics::SCREEN_HEIGHT / 2) - 30});
	mLevelTexture->Scale(Vec2_One*5.0f);
	mLevelTexture->Parent(this);

	mPlatforms.push_back(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 85 } , Graphics::SCREEN_WIDTH + 400));

	mPlatforms.push_back(new Platform({ 60 ,Graphics::SCREEN_HEIGHT - 250 }, 120));
	mPlatforms.push_back(new Platform({ Graphics::SCREEN_WIDTH - 60 ,Graphics::SCREEN_HEIGHT - 250 }, 120));

	mPlatforms.push_back(new Platform({ (Graphics::SCREEN_WIDTH / 2) + 77, Graphics::SCREEN_HEIGHT - 250 }, 80));
	mPlatforms.push_back(new Platform({ (Graphics::SCREEN_WIDTH / 2) - 77, Graphics::SCREEN_HEIGHT - 250 }, 80));

	mPlatforms.push_back(new Platform({ (Graphics::SCREEN_WIDTH / 2) + 150, (Graphics::SCREEN_WIDTH / 2) - 83 }, 100));
	mPlatforms.push_back(new Platform({ 150, (Graphics::SCREEN_WIDTH / 2) - 83 }, 100));

	mPlatforms.push_back(new Platform({ (Graphics::SCREEN_WIDTH / 2) + 77, 75 }, 80));
	mPlatforms.push_back(new Platform({ (Graphics::SCREEN_WIDTH / 2) - 77, 75 }, 80));

	mPlatforms.push_back(new Platform({ (Graphics::SCREEN_WIDTH) - 20, 75 }, 200));
	mPlatforms.push_back(new Platform({ 20, 75 }, 200));

	mWalls.push_back(new Wall({ 20,Graphics::SCREEN_HEIGHT - 85 }, 160));
	mWalls.push_back(new Wall({ Graphics::SCREEN_WIDTH - 20,Graphics::SCREEN_HEIGHT - 85 }, 160));

	mWalls.push_back(new Wall({220,Graphics::SCREEN_HEIGHT - 240 }, 320));
	mWalls.push_back(new Wall({Graphics::SCREEN_WIDTH - 220,Graphics::SCREEN_HEIGHT - 240 }, 320));

	mWalls.push_back(new Wall({ 20,Graphics::SCREEN_HEIGHT - 380 }, 300));
	mWalls.push_back(new Wall({Graphics::SCREEN_WIDTH - 20,Graphics::SCREEN_HEIGHT - 380 }, 300));

	mPlayer = player;

	mEnemies.push_back( new Bat({Graphics::SCREEN_WIDTH / 2,(Graphics::SCREEN_HEIGHT / 2) + 100}, mPlayer, true));
	mEnemies.push_back(new Torch({ 440,500 }, mPlayer));
	mEnemies.push_back(new Zombie({440,550},mPlayer));
}

Level::~Level() {
	delete mLevelTexture;
	mLevelTexture = nullptr;


	for (auto plat : mPlatforms) {
		delete plat;
		plat = nullptr;
	}

	for (auto wall : mWalls) {
		delete wall;
		wall = nullptr;
	}

	for (auto e : mEnemies) {
		delete e;
		e = nullptr;
	}

}

void Level::Update() {
	for (auto e : mEnemies) {
		e->Update();
	}
}

void Level::Render() {
	mLevelTexture->Render();
	for (auto plat : mPlatforms) {
		plat->Render();
	}
	for (auto wall : mWalls) {
		wall->Render();
	}
	for (int c = 0; c < mEnemies.size(); c++) {
		mEnemies[c]->Render();
	}
}