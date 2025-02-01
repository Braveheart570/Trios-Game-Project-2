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
			mStartScreen->ResetAnimation();
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
				
			}
		}
		else {
			mPlayScreen->Update();
		}
		
		break;
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
	}
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();

	mStartScreen = new StartScreen();

	mCurrentScreen = Start;
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;
}