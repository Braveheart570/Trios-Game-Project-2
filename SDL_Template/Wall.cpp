#include "Wall.h"

Wall::Wall(Vector2 pos, float height) : PhysEntity() {


	AddCollider(new BoxCollider({ 40,height }), {0,-height/2});
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Level);
	Position(pos);

}

Wall::~Wall() {

}