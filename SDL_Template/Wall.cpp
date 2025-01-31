#include "Wall.h"

Wall::Wall(Vector2 pos, float height) : PhysEntity() {

	mWidth = 40.0f;

	AddCollider(new BoxCollider({ mWidth,height }), {0,-height/2});
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Level);
	Position(pos);

}

Wall::~Wall() {

}

float Wall::Width() {
	return mWidth;
}