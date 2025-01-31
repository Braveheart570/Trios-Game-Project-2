#ifndef __PLAYER_H
#define __PLAYER_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Platform.h"
#include "wall.h"

using namespace SDLFramework;

class Player : public PhysEntity {
private:
	Timer * mTimer;
	InputManager * mInput;
	AudioManager * mAudio;

	int mScore;
	int mMaxLives;
	int mLives;
	bool mFacingRight;
	bool mCrouch;

	bool mInvulnerable;
	float mInvulnerableTime;
	float mInvulnerableDur;

	const float sGravity = 45;
	Vector2 mVelocity;
	const float mMaxVelocityMag = 100;
	const float mJumpStrength = 30.0f;
	Vector2 mPrevPos;
	bool mGrounded;

	GLTexture * mTexture;
	GLTexture* mCrouchTexture;
	GLTexture* mDeadTexture;

	float mMoveSpeed;
	Vector2 mMoveBounds;

	static const int MAX_BULLETS = 2;
	Bullet * mBullets[MAX_BULLETS];

private:
	void HandleMovement();
	void HandleFiring();
	void TakeHit();

public:
	Player();
	~Player();

	int Score();
	int Lives();

	void AddScore(int change);

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity * other) override;

	void Update() override;
	void Render() override;
};
#endif