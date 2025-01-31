#pragma once
#include "PhysEntity.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

using namespace SDLFramework;

class Wall : public PhysEntity {

public:

	Wall(Vector2 pos, float height = 160.0f);
	~Wall();

	float Width();

private:

	float mWidth;

};