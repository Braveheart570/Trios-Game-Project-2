#include "Platform.h"

Platform::Platform(Vector2 pos, float width) : PhysEntity(){

	AddCollider(new BoxCollider({width,5}), { 0,-5 / 2 });
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Level);
	Position(pos);

}


Platform::~Platform() {



}