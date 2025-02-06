#pragma once
#include "AnimatedGLTexture.h"


using namespace SDLFramework;


class ScrollingBG : public GameEntity {

public:

	ScrollingBG();
	~ScrollingBG();

	void Update() override;
	void Render() override;

	void ResetAnimations();

private:

	Timer* mTimer;

	GLTexture* mSky[3];
	GLTexture* mMoon;
	static const int sMountainPannels = 5;
	GLTexture* mMountains[sMountainPannels];

};