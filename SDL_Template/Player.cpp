#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"



Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mScore = 0;
	mMaxLives = 2;
	mLives = mMaxLives;
	mFacingRight = true;
	mCrouch = false;

	mInvulnerable = false;
	mInvulnerableTime = 0.0f;
	mInvulnerableDur = 3.0f;

	mVelocity = Vec2_Zero;
	mGrounded = false;
	
	mTexture = new AnimatedGLTexture("CarpathianSprites.png", 16, 0, 15, 16,4,0.5f, Animation::Layouts::Horizontal);
	mTexture->Parent(this);
	mTexture->Scale(Vec2_One*5.0f);
	mTexture->Position(Vec2_Up * -(mTexture->ScaledDimensions().y / 2));

	mCrouchTexture = new GLTexture("CarpathianSprites.png", 73, 3, 11, 13);
	mCrouchTexture->Parent(this);
	mCrouchTexture->Scale(Vec2_One*5.0f);
	mCrouchTexture->Position(Vec2_Up* -(mCrouchTexture->ScaledDimensions().y / 2));

	mMoveSpeed = 50.0f;
	mMoveBounds = Vector2(0.0f + mTexture->ScaledDimensions().x/2, Graphics::SCREEN_WIDTH - mTexture->ScaledDimensions().x/2);


	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i] = new Bullet(true);
	}

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()-Vec2_Right*10.0f), Vec2_Up * -42.0f);

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

	if (mInput->KeyDown(SDL_SCANCODE_RIGHT) && !mCrouch) {
		mVelocity += Vec2_Right * mMoveSpeed * mTimer->DeltaTime();
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT) && !mCrouch) {
		mVelocity += -Vec2_Right * mMoveSpeed * mTimer->DeltaTime();
	}

	if (mInput->KeyDown(SDL_SCANCODE_C) && mGrounded && !mCrouch) {

		mVelocity.y -= mJumpStrength;
		mGrounded = false;

	}
	 
	if (mInput->KeyDown(SDL_SCANCODE_DOWN)) {
		mCrouch = true;
	}
	else {
		mCrouch = false;
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
	if (mInput->KeyPressed(SDL_SCANCODE_X)) {
		for (int i = 0; i < MAX_BULLETS; ++i) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Position()+Vec2_Up* -30, mFacingRight);
				//mAudio->PlaySFX("SFX/Fire.wav");
				break;
			}
		}
	}
}

void Player::TakeHit() {
	mLives--;
	if (mLives <= 0) {
		//todo die
		return;
	}
	mInvulnerable = true;
	mInvulnerableTime = 0;


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
	return  mInvulnerable || !Active();
}

void Player::Hit(PhysEntity * other) {
	
	if (dynamic_cast<Platform*>(other) ) {
		if (mVelocity.y >= 0 && Position().y - other->Position().y >= 0) {
			Position({ Position().x,other->Position().y+1});
			mVelocity.y = 0.0f;
			mGrounded = true;
		}
	}else if (dynamic_cast<Wall*>(other)) {
		if (Position().x > other->Position().x) {
			mVelocity.x = 0.0f;
			Position(other->Position().x + ((mTexture->ScaledDimensions().x-10.0f) / 2) + (dynamic_cast<Wall*>(other)->Width() / 2), Position().y);//todo, box collider could do with some functions to get it's side.
		}
		else if (Position().x < other->Position().x) {
			mVelocity.x = 0.0f;
			Position(other->Position().x - ((mTexture->ScaledDimensions().x - 10.0f) / 2) - (dynamic_cast<Wall*>(other)->Width() / 2), Position().y);
		}
	}
	else if (false) {
		//todo heart
	}
	else {
		
	}

	
}

void Player::Update() {
	

	if (Active()) {

		if (abs(mVelocity.x) > 0.1f) {

			mTexture->Update();

		}

		HandleMovement();
		if (mVelocity.x > 0) {
			mFacingRight = true;
		}
		else if (mVelocity.x < 0) {
			mFacingRight = false;
		}
		HandleFiring();
	}
	

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}
}

void Player::Render() {
	if (Active()) {
		if (mCrouch) {
			mCrouchTexture->Render();
		}
		else {
			mTexture->Render();
		}
		
		PhysEntity::Render();
	}

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Render();
	}

	
	
}
