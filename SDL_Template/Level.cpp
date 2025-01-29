#include "level.h"

Level::Level(std::string texture, Player* player) {
	mLevelTexture = new GLTexture(texture);
	mLevelTexture->Position({ Graphics::SCREEN_WIDTH / 2,(Graphics::SCREEN_HEIGHT / 2) - 30});
	mLevelTexture->Scale(Vec2_One*5.0f);
	mLevelTexture->Parent(this);

	mPlatforms.push_back(new Platform({ Graphics::SCREEN_WIDTH / 2 ,Graphics::SCREEN_HEIGHT - 65 } ,{ Graphics::SCREEN_WIDTH + 400,50 }));
	mPlatforms.push_back(new Platform({ 100 ,Graphics::SCREEN_HEIGHT - 200 }, { 200,50 }));

	mPlayer = player;

	testBat = new Bat({ Graphics::SCREEN_WIDTH / 2,Graphics::SCREEN_HEIGHT / 2 }, player, true);
}

Level::~Level() {
	delete mLevelTexture;
	mLevelTexture = nullptr;


	for (auto plat : mPlatforms) {
		delete plat;
		plat = nullptr;
	}

}

void Level::Update() {
	testBat->Update();
}

void Level::Render() {
	mLevelTexture->Render();
	for (auto plat : mPlatforms) {
		plat->Render();
	}
	testBat->Render();
}