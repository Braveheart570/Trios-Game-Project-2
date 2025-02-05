#include "Zombie.h"

Zombie::Zombie(Vector2 pos, Player* player) : Enemy(new AnimatedGLTexture("CarpathianSprites.png",133,0,16,16,2,0.75f,Animation::Layouts::Horizontal),player,200,3) {
	
	Position(pos);

	nWanderXRight = pos.x + mWanderDist;
	mWanderXLeft = pos.x - mWanderDist;

	mFacingRight = false;

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

}

Zombie::Zombie(AnimatedGLTexture* tex, Vector2 pos, Player* player) : Enemy(tex, player, 200, 3) {

	Position(pos);

	nWanderXRight = pos.x + mWanderDist;
	mWanderXLeft = pos.x - mWanderDist;

	mFacingRight = false;

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

}

Zombie::~Zombie() {

}

void Zombie::Update() {

	mTexture->Update();

	if (mFacingRight) {
		Translate(Vec2_Right * mSpeed * mTimer->DeltaTime());

		if (Position().x >= nWanderXRight) {
			Position(nWanderXRight, Position().y);
			mFacingRight = false;
			mTexture->Flip(false,false);
		}
	}
	else {
		Translate(-Vec2_Right*mSpeed*mTimer->DeltaTime());

		if (Position().x <= mWanderXLeft) {
			Position(mWanderXLeft,Position().y);
			mFacingRight = true;
			mTexture->Flip(true,false);
		}
	}

}