#pragma once
#include "Enemy.h"

class Torch : public Enemy {

public:

	Torch(Vector2 pos, Player* player);
	~Torch();

	virtual void Update() override;

};