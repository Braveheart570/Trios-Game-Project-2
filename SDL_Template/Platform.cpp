#include "Platform.h"

Platform::Platform(Vector2 pos, Vector2 size) : PhysEntity(){

	AddCollider(new BoxCollider(size));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Level);
	Position(pos);

}


Platform::~Platform() {



}