#ifndef __STARTSCREEN_H
#define __STARTSCREEN_H
#include "AnimatedGLTexture.h"
#include "InputManager.h"
#include "Scoreboard.h"
#include "ScrollingBG.h";

using namespace SDLFramework;

class StartScreen : public GameEntity {

private:

	Timer * mTimer;
	InputManager * mInput;

	ScrollingBG* mBackground;

	GLTexture* mTitle;


public:
	StartScreen();
	~StartScreen();

	void ResetAnimation();

	void Update() override;
	void Render() override;
};
#endif