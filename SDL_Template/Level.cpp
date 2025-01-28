#include "level.h"

Level::Level(std::string texture) {
	mLevelTexture = new GLTexture(texture);
	mLevelTexture->Position({ Graphics::SCREEN_WIDTH / 2,(Graphics::SCREEN_HEIGHT / 2) - 30});
	mLevelTexture->Scale(Vec2_One*5.0f);
	mLevelTexture->Parent(this);

	mLevelGeo.push_back(BoxCollider(Vec2_One*5.0f));
	mLevelGeo[0].Position({Graphics::SCREEN_WIDTH/2,Graphics::SCREEN_HEIGHT/2});
	mLevelGeo[0].Parent(this);
}

Level::~Level() {
	delete mLevelTexture;
	mLevelTexture = nullptr;
}

void Level::Update() {

}

void Level::Render() {
	mLevelTexture->Render();
	for (auto box : mLevelGeo) {
		box.Render();
	}
}