#ifndef __STARTSCREEN_H
#define __STARTSCREEN_H
#include "AnimatedGLTexture.h"
#include "InputManager.h"
#include "Scoreboard.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {

private:

	Timer * mTimer;
	InputManager * mInput;

	GLTexture* mSky[3];
	GLTexture* mMoon;
	static const int sMountainPannels = 5;
	GLTexture* mMountains[sMountainPannels];
	GLTexture* mTitle;


public:
	StartScreen();
	~StartScreen();

	void ResetAnimation();

	void Update() override;
	void Render() override;
};
#endif