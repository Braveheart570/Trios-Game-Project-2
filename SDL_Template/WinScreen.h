#pragma once
#include "InputManager.h"
#include "AudioManager.h"
#include "ScrollingBG.h"

using namespace SDLFramework;

class WinScreen : public GameEntity {

public:

	WinScreen();
	~WinScreen();

	void Update() override;
	void Render() override;

private:

	Timer* mTimer;

	ScrollingBG* mBackground;
	
	GLTexture* mText1;
	GLTexture* mText2;
	GLTexture* mText3;
	GLTexture* mText4;
};