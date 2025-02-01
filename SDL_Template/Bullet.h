#ifndef __BULLET_H
#define __BULLET_H
#include "PhysEntity.h"
#include "Timer.h"
#include "AnimatedGLTexture.h"
#include "AudioManager.h"

using namespace SDLFramework;

class Bullet : public PhysEntity {
protected:
	static const int OFFSCREEN_BUFFER = 10;

	Timer * mTimer;

	Texture * mTexture;

	float mSpeed;

	Vector2 mDir;

	//Inherited from PhysEntity
	bool IgnoreCollisions() override;

	Bullet(AnimatedGLTexture* tex);

public:
	Bullet(bool friendly);
	~Bullet();

	void Fire(Vector2 pos, Vector2 dir);
	void Reload();

	// Inherited from PhysEntity
	void Hit(PhysEntity * other) override;

	void Update() override;
	void Render() override;
};
#endif