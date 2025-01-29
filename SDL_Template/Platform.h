#pragma once
#include "PhysEntity.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

using namespace SDLFramework;


class Platform : public PhysEntity {


public:

	Platform(Vector2 pos,Vector2 size);
	~Platform();

private:


};