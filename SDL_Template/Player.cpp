#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"



Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mScore = 0;
	mMaxHealth = 10;
	mHealth = mMaxHealth;
	mFacingRight = true;
	mCrouch = false;

	mVisable = true;
	mFlashTime = 0.0f;
	mFlashInterval = 0.2f;

	mFiring = false;
	mFireTime = 0.0f;
	mFireDur = 0.15f;
	mBulletYOffset = -65.0f;
	mBulletYOffsetCrouch = -30.0f;

	mDead = false;

	mInvulnerable = false;
	mInvulnerableTime = 0.0f;
	mInvulnerableDur = 3.0f;

	mVelocity = Vec2_Zero;
	mGrounded = false;
	
	mTexture = new AnimatedGLTexture("CarpathianSprites.png", 16, 0, 14, 16,4,0.5f, Animation::Layouts::Horizontal);
	mTexture->Parent(this);
	mTexture->Scale(Vec2_One*5.0f);
	mTexture->Position(Vec2_Up * -(mTexture->ScaledDimensions().y / 2));

	mCrouchTexture = new GLTexture("CarpathianSprites.png", 73, 3, 11, 13);
	mCrouchTexture->Parent(this);
	mCrouchTexture->Scale(Vec2_One*5.0f);
	mCrouchTexture->Position(Vec2_Up* -(mCrouchTexture->ScaledDimensions().y / 2));

	mDeadTexture = new GLTexture("CarpathianSprites.png", 17, 17, 16, 8);
	mDeadTexture->Parent(this);
	mDeadTexture->Scale(Vec2_One*5.0f);
	mDeadTexture->Position(Vec2_Up * -(mDeadTexture->ScaledDimensions().y / 2));

	mFiringTexture = new GLTexture("CarpathianSprites.png",0,0,15,16);
	mFiringTexture->Parent(this);
	mFiringTexture->Scale(Vec2_One * 5.0f);
	mFiringTexture->Position(Vec2_Up * -(mFiringTexture->ScaledDimensions().y / 2));

	mCrouchFireTexture = new GLTexture("CarpathianSprites.png",86,3,13,13);
	mCrouchFireTexture->Parent(this);
	mCrouchFireTexture->Scale(Vec2_One * 5.0f);
	mCrouchFireTexture->Position(Vec2_Up * -(mCrouchFireTexture->ScaledDimensions().y / 2));

	mMoveSpeed = 50.0f;
	mMoveBounds = Vector2(0.0f - mTexture->ScaledDimensions().x, Graphics::SCREEN_WIDTH + mTexture->ScaledDimensions().x);


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

	delete mCrouchTexture;
	mCrouchTexture = nullptr;

	delete mDeadTexture;
	mDeadTexture = nullptr;

	delete mFiringTexture;
	mFiringTexture = nullptr;

	delete mCrouchFireTexture;
	mCrouchFireTexture = nullptr;

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

		mAudio->PlaySFX("SFX/Jump.wav");
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
		pos.x = mMoveBounds.y;
	}
	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.x;
	}

	Position(pos);
}

void Player::HandleFiring() {
	if (mInput->KeyPressed(SDL_SCANCODE_X)) {
		for (int i = 0; i < MAX_BULLETS; ++i) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Position()+Vec2_Up* (mCrouch ? mBulletYOffsetCrouch : mBulletYOffset), mFacingRight ? Vec2_Right : -Vec2_Right);
				mAudio->PlaySFX("SFX/Throw.wav");
				mFiring = true;
				break;
			}
		}
	}
}

void Player::TakeHit() {
	mAudio->PlaySFX("SFX/TakeDamage.wav");
	mHealth--;
	if (mHealth <= 0) {
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
	return mHealth;
}

void Player::AddScore(int change) {
	mScore += change;
}

bool Player::IgnoreCollisions()
{
	return !Active();
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
	else if (dynamic_cast<Heart*>(other) && mHealth < mMaxHealth) {
		mHealth++;
	}
	else if (dynamic_cast<Bullet*>(other) && !mInvulnerable) {
		TakeHit();
	}

	//NOTE to avoid cyclical reference enemy contact damage is delt in the Enemy Class


	
}

void Player::Update() {
	
	if (!mDead && mHealth <= 0) {
		mAudio->PauseMusic();
		mAudio->PlaySFX("SFX/Die.wav");
		mDead = true;
	}


	if (Active() && !mDead) {

		if (abs(mVelocity.x) > 0.1f) {

			mTexture->Update();

		}

		HandleMovement();

		if (mVelocity.x > 0) {
			mFacingRight = true;
			if (mTexture->Flipped()) mTexture->Flip(false, false);
			if (mCrouchTexture->Flipped()) mCrouchTexture->Flip(false, false);
			if (mFiringTexture->Flipped()) mFiringTexture->Flip(false, false);
			if (mCrouchFireTexture->Flipped()) mCrouchFireTexture->Flip(false, false);
		}
		else if (mVelocity.x < 0) {
			mFacingRight = false;
			if (!mTexture->Flipped()) mTexture->Flip(true, false);
			if (!mCrouchTexture->Flipped()) mCrouchTexture->Flip(true, false);
			if (!mFiringTexture->Flipped()) mFiringTexture->Flip(true, false);
			if (!mCrouchFireTexture->Flipped()) mCrouchFireTexture->Flip(true, false);
		}
		HandleFiring();
	}
	
	if (mFiring) {
		mFireTime += mTimer->DeltaTime();
		if (mFireTime >= mFireDur) {
			mFiring = false;
			mFireTime = 0.0f;
		}
	}
	if (mInvulnerable) {
		mInvulnerableTime += mTimer->DeltaTime();
		if (mInvulnerableTime >= mInvulnerableDur) {
			mInvulnerable = false;
			mInvulnerableTime = 0.0f;
			mVisable = true;
			mFlashTime = 0.0f;
		}
		else {
			mFlashTime += mTimer->DeltaTime();
			if (mFlashTime >= mFlashInterval) {
				mVisable = !mVisable;
				mFlashTime = 0.0f;
			}
		}
	}

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}
}

void Player::Render() {
	
	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Render();
	}

	if (!Active()) {
		return;
	}

	if (mDead) {
		mDeadTexture->Render();

	}
	else if (mVisable) {

		if (mCrouch) {
			if (mFiring) {
				mCrouchFireTexture->Render();
			}
			else {
				mCrouchTexture->Render();
			}

		}
		else {
			if (mFiring) {
				mFiringTexture->Render();
			}
			else {
				mTexture->Render();
			}
		}
		
		PhysEntity::Render();
	}

	
	
}

bool Player::Invulnerable() {
	return mInvulnerable;
}

int Player::MaxHeath() {
	return mMaxHealth;
}

void Player::UpgradeHealth() {
	mMaxHealth = 15;
	mHealth = mMaxHealth;
}

int Player::Health() {
	return mHealth;
}

bool Player::Dead() {
	return mDead;
}