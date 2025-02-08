#pragma once
#include "PhysEntity.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "AudioManager.h"
#include "AnimatedGLTexture.h"

class Heart : public PhysEntity {

public:

	Heart();
	~Heart();

	void Spawn(Vector2 pos);

	void Render() override;

	void Update() override;

	void Hit(PhysEntity* other) override;

private:

	GLTexture* mtexture;

};