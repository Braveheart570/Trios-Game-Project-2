#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"



Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = true;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 2;

	mVelocity = Vec2_Zero;
	mGrounded = false;
	
	mTexture = new GLTexture("PlayerShips.png", 0, 0, 60, 64);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);

	mMoveSpeed = 50.0f;
	mMoveBounds = Vector2(0.0f + mTexture->ScaledDimensions().x/2, Graphics::SCREEN_WIDTH - mTexture->ScaledDimensions().x/2);


	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i] = new Bullet(true);
	}

	AddCollider(new BoxCollider(Vector2(32.0f, 48.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mTexture;
	mTexture = nullptr;

	for (auto b : mBullets) {
		delete b;
	}
}

void Player::HandleMovement() {

	mVelocity.y += sGravity * mTimer->DeltaTime();

	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		mVelocity += Vec2_Right * mMoveSpeed * mTimer->DeltaTime();
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		mVelocity += -Vec2_Right * mMoveSpeed * mTimer->DeltaTime();
	}

	if (mInput->KeyDown(SDL_SCANCODE_C) && mGrounded) {

		mVelocity.y -= mJumpStrength;
		mGrounded = false;

	}
	else if (mInput->KeyDown(SDL_SCANCODE_S)) {

	}
	
	//drag
	if (mVelocity.Magnitude() < 0.2f) {
		mVelocity = Vec2_Zero;
	}
	else {
		mVelocity = mVelocity.Normalized() * mVelocity.Magnitude() * 0.9f;
	}
	// velocity cap
	if (mVelocity.Magnitude() > mMaxVelocityMag) mVelocity = mVelocity.Normalized() * mMaxVelocityMag;



	
	

	
	mPrevPos = Position();
	Translate(mVelocity);

	Vector2 pos = Position(Local);
	if (pos.x < mMoveBounds.x) {
		pos.x = mMoveBounds.x;
	}
	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.y;
	}

	Position(pos);
}

void Player::HandleFiring() {
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
		for (int i = 0; i < MAX_BULLETS; ++i) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Position());
				mAudio->PlaySFX("SFX/Fire.wav");
				break;
			}
		}
	}
}

void Player::Visible(bool visible) {
	mVisible = visible;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

void Player::AddScore(int change) {
	mScore += change;
}

bool Player::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Player::Hit(PhysEntity * other) {
	
	if (dynamic_cast<Level*>(other)) {
		//std::cout << "hit Floor" << std::endl;
		Position({Position().x,mPrevPos.y});
		mVelocity.y = 0.0f;
		mGrounded = true;
		return;
	}
	mLives -= 1;
	mAnimating = true;
	mAudio->PlaySFX("SFX/PlayerExplosion.wav");
	mWasHit = true;
}

bool Player::WasHit() {
	return mWasHit;
}

void Player::Update() {
	if (mAnimating) {

		if (mWasHit) {
			mWasHit = false;
		}

	}
	else {
		if (Active()) {
			HandleMovement();
			HandleFiring();
		}
	}

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}
}

void Player::Render() {
	if (mVisible) {
		if (mAnimating) {
		}
		else {
			//mTexture->Render();
		}
	}

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Render();
	}

	PhysEntity::Render();
}
