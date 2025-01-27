#pragma once
#include "Texture.h"
#include <vector>

using namespace SDLFramework;

class Level : public GameEntity {

public:

	Level();
	~Level();

	void Update() override;
	void Render() override;

private:

	Texture* mLevelTexture;

	std::vector<Texture*> mEnemies;

	Vector2 mPlayerStart;

};