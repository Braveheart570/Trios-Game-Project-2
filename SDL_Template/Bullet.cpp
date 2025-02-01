#include "Bullet.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

bool Bullet::IgnoreCollisions() {
	return !Active();
}

Bullet::Bullet(bool friendly) {
	mTimer = Timer::Instance();
	if (friendly) {
		mTexture = new GLTexture("CarpathianSprites.png", 4, 27, 8, 4);
	}
	else {
		mTexture = new AnimatedGLTexture("CarpathianSprites.png", 0, 17, 8, 8, 2, 0.5f, Animation::Layouts::Horizontal);
	}
	
	mTexture->Parent(this);
	mTexture->Scale(Vec2_One * 5.0f);
	mTexture->Position(Vec2_Zero);

	mSpeed = 500;

	Reload();

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	if (friendly) {
		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::FriendlyProjectiles);
	}
	else {
		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::HostileProjectiles);
	}
}

Bullet::~Bullet() {
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void Bullet::Fire(Vector2 pos, bool right) {
	mFireRight = right;
	if (mFireRight) {
		mTexture->Flip(false, false);
	}
	else {
		mTexture->Flip(true, false);
	}
	Position(pos);
	Active(true);
}

void Bullet::Reload() {
	Active(false);
}

void Bullet::Hit(PhysEntity * other) {
	AudioManager::Instance()->PlaySFX("SFX/Hit.wav");
	Reload();
}

void Bullet::Update() {
	if (Active()) {

		mTexture->Update();

		if (mFireRight) {
			Translate(Vec2_Right * mSpeed * mTimer->DeltaTime());
		}
		else {
			Translate(-Vec2_Right * mSpeed * mTimer->DeltaTime());
		}
		

		Vector2 pos = Position();
		if (pos.x < -OFFSCREEN_BUFFER || pos.x > Graphics::SCREEN_WIDTH + OFFSCREEN_BUFFER) {
			Reload();
		}
	}
}

void Bullet::Render() {
	if (Active()) {
		mTexture->Render();
		PhysEntity::Render();
	}
}
