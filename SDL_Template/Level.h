#pragma once
#include "GLTexture.h"
#include <vector>
#include "PhysicsManager.h"
#include "physEntity.h"
#include "Platform.h"
#include "Wall.h"
#include "Bat.h"
#include "Player.h"
#include "Torch.h"
#include "Zombie.h"
#include "Fishman.h"
#include "heart.h"

using namespace SDLFramework;

class Level : public GameEntity {

public:

	Level(std::string texture, Player* player);
	~Level();

	void Update() override;
	void Render() override;

	void AddPlatform(Platform* platform);
	void AddWall(Wall* wall);
	void AddEnemy(Enemy* enemy);

	bool LevelComplete(); // not using this yet

	void CollidersActive(bool active);

private:

	GLTexture* mLevelTexture;

	Player* mPlayer;

	std::vector<Platform*> mPlatforms;
	std::vector<Wall*> mWalls;

	std::vector<Enemy*> mEnemies;

	static const int MAX_HEARTS = 4;
	Heart* mHearts[MAX_HEARTS];

	Vector2 mPlayerStart;
};