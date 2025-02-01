#pragma once
#include "bat.h"

class RedBat : public Bat {

public:
	RedBat(Vector2 pos, Player* player, bool left);
	~RedBat();

};