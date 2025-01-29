#pragma once
#include "Enemy.h"
#include "Player.h"

class Bat : public Enemy {

public:

	Bat(Vector2 pos, Player* player, bool left = true);
	~Bat();

	virtual void Update() override;

private:

	bool mLeft;
	bool mTrackingPlayer;
	int mYTrigger;
	Player* mPlayer;

};