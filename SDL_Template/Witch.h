#pragma once
#include "Pumpkin.h"

class Witch : public Pumpkin {

public:

	Witch(Vector2 pos, Player* player);
	~Witch();


private:

	void Fire() override;

};