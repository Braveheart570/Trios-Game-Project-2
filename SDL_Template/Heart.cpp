#include "Heart.h"

Heart::Heart() {

	mtexture = new AnimatedGLTexture("CarpathianSprites.png",33,35,8,6,2,0.5f,Animation::Layouts::Horizontal);
	mtexture->Parent(this);
	mtexture->Scale(Vec2_One * 5.0f);

	AddCollider(new BoxCollider(mtexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Consumable);

	Active(false);

}

Heart::~Heart() {
	delete mtexture;
	mtexture = nullptr;
}

void Heart::Spawn(Vector2 pos) {
	Active(true);
	AudioManager::Instance()->PlaySFX("SFX/HeartSpawn.wav");
	Position(pos);
}

void Heart::Render() {
	if (Active()) {
		mtexture->Render();
		PhysEntity::Render();
	}
}

void Heart::Update() {
	mtexture->Update();
}

void Heart::Hit(PhysEntity* other) {
	AudioManager::Instance()->PlaySFX("SFX/HeartGotten.wav");
	Active(false);
}