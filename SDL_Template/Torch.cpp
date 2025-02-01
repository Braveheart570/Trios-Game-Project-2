#include "Torch.h"

Torch::Torch(Vector2 pos, Player* player) : Enemy(new AnimatedGLTexture("carpathianSprites.png",0,61,9,8,4,0.7f,Animation::Layouts::Horizontal),player, 100) {
	mDamageOnContact = false;

	Position(pos);

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

}

Torch::~Torch() {

}

void Torch::Update() {

	if (!Active()) {
		return;
	}

	mTexture->Update();

}