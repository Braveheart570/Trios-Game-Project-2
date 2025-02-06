 #include "ScreenManager.h"

ScreenManager * ScreenManager::sInstance = nullptr;

ScreenManager * ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void ScreenManager::Update() {

	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_X)) {
			mCurrentScreen = Play;
			AudioManager::Instance()->PauseMusic();
			AudioManager::Instance()->PlaySFX("SFX/startSound.wav");
			mPlayScreen = new PlayScreen();
		}
		break;
	case Play:
		if (mPlayScreen->GameOver()) {
			if (mInput->KeyPressed(SDL_SCANCODE_X)) {
				mCurrentScreen = Start;
				delete mPlayScreen;
				mStartScreen->ResetAnimation();
				AudioManager::Instance()->PlayMusic("Music/menuMusic.wav");
				
			}
		}
		else {
			mPlayScreen->Update();
			if (mPlayScreen->Win()) {
				delete mPlayScreen;
				mCurrentScreen = Win;
				AudioManager::Instance()->PlayMusic("Music/menuMusic.wav");
			}
		}
		
		break;
	case Win:
		mWinScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_X)) {
			mCurrentScreen = Start;
			mStartScreen->ResetAnimation();
		}
	}
}

void ScreenManager::Render() { 
	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Render();
		break;
	case Play:
		mPlayScreen->Render();
		break;
	case Win:
		mWinScreen->Render();
		break;
	}
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();

	mStartScreen = new StartScreen();

	mWinScreen = new WinScreen();

	mCurrentScreen = Start;
	AudioManager::Instance()->PlayMusic("Music/menuMusic.wav");
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;
}