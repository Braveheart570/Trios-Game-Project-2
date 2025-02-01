#include "Witch.h"

Witch::Witch(Vector2 pos, Player* player) : Pumpkin(new GLTexture("CarpathianSprites.png",128,17,16,14), new GLTexture("CarpathianSprites.png",145,17,16,14), pos, player) {
	mHealth = 3;
	mPts = 1000;
	mYTrigger = Graphics::SCREEN_HEIGHT;
}

Witch::~Witch() {

}


void Witch::Fire() {

	Vector2 dirs[8] = { {0,1},{1,1},{1,0},{1,-1},{-1,0},{-1,-1},{-1,0},{-1,1} };

	mFiring = true;
	for (int c = 0; c < 8; c++) {
		for (int i = 0; i < MAX_BULLETS; ++i) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Position() + Vec2_Up * -30, dirs[c]);
				break;
			}
		}
	}
	

}