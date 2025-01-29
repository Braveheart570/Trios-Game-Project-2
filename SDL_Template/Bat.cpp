#include "Bat.h"


Bat::Bat(Vector2 pos, Player* player, bool left) : Enemy(new AnimatedGLTexture("CarpathianSprites.png",1,43,8,8,3,0.7f,Animation::Layouts::Horizontal),100) {

	Position(pos);
	mLeft = left;
	mPlayer = player;

	mYTrigger = 40;
	mTrackingPlayer = false;

}

Bat::~Bat() {
	mPlayer = nullptr;
}

void Bat::Update() {
	dynamic_cast<AnimatedGLTexture*>(mTexture)->Update();
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

		if (mPlayer->Position().y < Position().y) {
			Translate(-Vec2_Up * (mSpeed/2)*mTimer->DeltaTime());
		}
		else if (mPlayer->Position().y > Position().y) {
			Translate(Vec2_Up*(mSpeed/2)*mTimer->DeltaTime());
		}


	}
	else if (abs(mPlayer->Position().y - Position().y) < mYTrigger) {
		mTrackingPlayer = true;
	}
	
}