#pragma once
#include "Zombie.h"
#include "Bone.h"

class Skeleton : public Zombie {

public:

	Skeleton(Vector2 pos, Player* player);
	~Skeleton();

	void Update() override;
	void Render() override;

private:


	float mFireTime;
	float mFireInterval;

	static const int MAX_BONES = 2;
	Bone* mBones[MAX_BONES];
	void Fire();

};