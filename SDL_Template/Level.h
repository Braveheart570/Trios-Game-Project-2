#pragma once
#include "GLTexture.h"
#include <vector>
#include "PhysicsManager.h"
#include "physEntity.h"
#include "Platform.h"
#include "Bat.h"
#include "Player.h"

using namespace SDLFramework;

class Level : public GameEntity {

public:

	Level(std::string texture, Player* player);
	~Level();

	void Update() override;
	void Render() override;

private:

	GLTexture* mLevelTexture;

	Player* mPlayer;

	std::vector<Platform*> mPlatforms;

	Bat* testBat;

	Vector2 mPlayerStart;
};