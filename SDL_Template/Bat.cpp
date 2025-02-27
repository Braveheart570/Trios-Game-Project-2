#include "Bat.h"


Bat::Bat(Vector2 pos, Player* player, bool left) : Enemy(new AnimatedGLTexture("CarpathianSprites.png",1,43,8,8,3,0.7f,Animation::Layouts::Horizontal), player,200) {

	Position(pos);
	mLeft = left;

	mYTrigger = 200;
	mTrackingPlayer = false;
	mPlayerOriginOffset = -60;

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	if (!mLeft) mTexture->Flip(true,false);

}

Bat::Bat(AnimatedGLTexture* tex, Vector2 pos, Player* player, bool left) : Enemy(tex, player, 200) {

	Position(pos);
	mLeft = left;

	mYTrigger = 200;
	mTrackingPlayer = false;
	mPlayerOriginOffset = -30;

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	if (!mLeft) mTexture->Flip(true, false);

}


Bat::~Bat() {
	
}

void Bat::Update() {

	if (!Active()) {
		return;
	}

	mTexture->Update();

	if (mLeft) {
		Translate(Vec2_Right * -mSpeed * mTimer->DeltaTime());
	}
	else {
		Translate(Vec2_Right * mSpeed * mTimer->DeltaTime());
	}

	if (Position().x <= -100) {
		Position(Graphics::SCREEN_WIDTH + 100, Position().y);
	}
	else if (Position().x >= Graphics::SCREEN_WIDTH + 100) {
		Position(-100,Position().y);
	}

	if (mTrackingPlayer) {

		if (mPlayer->Position().y+ mPlayerOriginOffset < Position().y) {
			Translate(-Vec2_Up * (mSpeed/2)*mTimer->DeltaTime());
		}
		else if (mPlayer->Position().y + mPlayerOriginOffset > Position().y) {
			Translate(Vec2_Up*(mSpeed/2)*mTimer->DeltaTime());
		}


	}
	else if (abs(mPlayer->Position().y - Position().y) < mYTrigger) {
		mTrackingPlayer = true;
	}
	
}