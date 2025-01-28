#pragma once
#include "GLTexture.h"
#include <vector>
#include "physEntity.h"
#include "BoxCollider.h"

using namespace SDLFramework;

class Level : public PhysEntity {

public:

	Level(std::string texture);
	~Level();

	void Update() override;
	void Render() override;

private:

	GLTexture* mLevelTexture;

	Vector2 mPlayerStart;
};