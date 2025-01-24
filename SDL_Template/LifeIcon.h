#pragma once
#include "GlTexture.h"

using namespace SDLFramework;

class LifeIcon : public GameEntity {

public:

	LifeIcon(float x = 0.0f, float y = 0.0f);
	LifeIcon(const Vector2& position);

	virtual ~LifeIcon();

	void Render() override;

private:

	GLTexture* mActiveTex;
	GLTexture* mInactiveTex;

	void Init();


};