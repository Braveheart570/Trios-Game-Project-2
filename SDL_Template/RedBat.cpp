#include "RedBat.h"

RedBat::RedBat(Vector2 pos, Player* player, bool left) : Bat(new AnimatedGLTexture("CarpathianSprites.png", 1, 51, 8, 8, 3, 0.5f, Animation::Layouts::Horizontal),pos,player,left) {
	mHealth = 2;
	mPts = 400;
}

RedBat::~RedBat() {

}