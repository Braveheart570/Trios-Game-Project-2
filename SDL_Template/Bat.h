#pragma once
#include "Enemy.h"

class Bat : public Enemy {

public:

	Bat(Vector2 pos, Player* player, bool left = true);
	
	~Bat();

	virtual void Update() override;

protected:

	bool mLeft;
	bool mTrackingPlayer;
	int mYTrigger;
	int mPlayerOriginOffset;

	Bat(AnimatedGLTexture* tex, Vector2 pos, Player* player, bool left = true);

};