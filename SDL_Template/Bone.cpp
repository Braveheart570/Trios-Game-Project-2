#include "Bone.h"

Bone::Bone() : Bullet(new AnimatedGLTexture("CarpathianSprites.png", 27, 43, 6, 6, 4, 0.5f, Animation::Layouts::Horizontal)) {
	mSpeed = mSpeed * 0.6f;
}

Bone::~Bone() {

}