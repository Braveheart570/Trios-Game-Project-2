#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H
#include "StartScreen.h"
#include "PlayScreen.h"
#include "AudioManager.h"
#include "WinScreen.h"

class ScreenManager {
private:
	static ScreenManager * sInstance;

	enum Screens { Start, Play, Win };
	Screens mCurrentScreen;

	InputManager * mInput;

	StartScreen * mStartScreen;
	PlayScreen * mPlayScreen;
	WinScreen* mWinScreen;

public:
	static ScreenManager * Instance();
	static void Release();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};
#endif