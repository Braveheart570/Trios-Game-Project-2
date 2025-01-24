#include "LifeIcon.h"

LifeIcon::LifeIcon(float x, float y) : GameEntity(x,y){
	Init();
}

LifeIcon::LifeIcon(const Vector2& position) : GameEntity(position) {
	Init();
}

LifeIcon::~LifeIcon() {
	delete mActiveTex;
	mActiveTex = nullptr;
	delete mInactiveTex;
	mInactiveTex = nullptr;
}

void LifeIcon::Render() {
	if (Active()) {
		mActiveTex->Render();
	}
	else {
		mInactiveTex->Render();
	}
}


void LifeIcon::Init() {

	mActiveTex = new GLTexture("CarpathianSprites.png",0,27,2,5);
	mActiveTex->Parent(this);
	mActiveTex->Position(Vec2_Zero);
	mActiveTex->Scale(Vec2_One*5.0f);

	mInactiveTex = new GLTexture("CarpathianSprites.png", 3, 27, 2, 5);
	mInactiveTex->Parent(this);
	mInactiveTex->Position(Vec2_Zero);
	mInactiveTex->Scale(Vec2_One * 5.0f);

	

}

