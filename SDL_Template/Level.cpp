#include "level.h"

Level::Level(std::string texture, Player* player) {
	mLevelTexture = new GLTexture(texture);
	mLevelTexture->Position({ Graphics::SCREEN_WIDTH / 2,(Graphics::SCREEN_HEIGHT / 2) - 30});
	mLevelTexture->Scale(Vec2_One*5.0f);
	mLevelTexture->Parent(this);

	mPlayer = player;

	for (int c = 0; c < MAX_HEARTS; c++) {
		mHearts[c] = new Heart();
	}
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

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_H)) {
		for (int i = 0; i < MAX_HEARTS; ++i) {
			if (!mHearts[i]->Active()) {
				mHearts[i]->Spawn({400,500});
				break;
			}
		}
	}

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

	for (int c = 0; c < MAX_HEARTS; c++) {
		mHearts[c]->Render();
	}
}

void Level::AddPlatform(Platform* platform) {
	mPlatforms.push_back(platform);
}

void Level::AddWall(Wall* wall) {
	mWalls.push_back(wall);
}

void Level::AddEnemy(Enemy* enemy) {
	mEnemies.push_back(enemy);
}

bool Level::LevelComplete() {
	for (auto e : mEnemies) {
		if (e->Active()) return false;
	}
	return true;
}

void Level::CollidersActive(bool active) {

	for (auto p : mPlatforms) {
		p->Active(active);
	}

	for (auto w : mWalls) {
		w->Active(active);
	}

	for (auto e : mEnemies) {
		e->Active(active);
	}

}