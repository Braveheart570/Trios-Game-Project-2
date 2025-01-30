#include "Bullet.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

bool Bullet::IgnoreCollisions() {
	return !Active();
}

Bullet::Bullet(bool friendly) {
	mTimer = Timer::Instance();

	mTexture = new GLTexture("GalagaAssets/Bullet.png");
	mTexture->Parent(this);
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
	Position(pos);
	Active(true);
}

void Bullet::Reload() {
	Active(false);
}

void Bullet::Hit(PhysEntity * other) {
	std::cout << Position().x << " | " << Position().y << std::endl;
	Reload();
}

void Bullet::Update() {
	if (Active()) {
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
