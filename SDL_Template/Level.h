#pragma once
#include "GLTexture.h"
#include <vector>
#include "BoxCollider.h"

using namespace SDLFramework;

class Level : public GameEntity {

public:

	Level(std::string texture);
	~Level();

	void Update() override;
	void Render() override;

private:

	GLTexture* mLevelTexture;

	Vector2 mPlayerStart;

	std::vector<BoxCollider> mLevelGeo;
};