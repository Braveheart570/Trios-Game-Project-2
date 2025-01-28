#include "level.h"

Level::Level(std::string texture) {
	mLevelTexture = new GLTexture(texture);
	mLevelTexture->Position({ Graphics::SCREEN_WIDTH / 2,(Graphics::SCREEN_HEIGHT / 2) - 30});
	mLevelTexture->Scale(Vec2_One*5.0f);
	mLevelTexture->Parent(this);

	AddCollider(new BoxCollider({ Graphics::SCREEN_WIDTH+400,50 }), { Graphics::SCREEN_WIDTH/2 ,Graphics::SCREEN_HEIGHT - 65 });
	AddCollider(new BoxCollider({ 200,50 }), { 100 ,Graphics::SCREEN_HEIGHT - 200 });

	mId = PhysicsManager::Instance()->RegisterEntity(this,PhysicsManager::CollisionLayers::Level);
}

Level::~Level() {
	delete mLevelTexture;
	mLevelTexture = nullptr;
}

void Level::Update() {

}

void Level::Render() {
	mLevelTexture->Render();
	PhysEntity::Render();
}