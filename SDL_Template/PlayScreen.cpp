#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.9f);

	mLifeLabel = new GLTexture("life:", "pico-8-mono-upper.ttf", 25, {255,204,170});
	mLifeLabel->Position({60,Graphics::SCREEN_HEIGHT-30});
	mLifeLabel->Parent(this);

	for (int c = 0; c < 10; c++) {
		mLifeIcons.push_back(new LifeIcon(110 + (c*15), Graphics::SCREEN_HEIGHT - 30));
		mLifeIcons[c]->Parent(this);
	}

	mScoreLabel = new GLTexture("score:", "pico-8-mono-upper.ttf", 25, {255,204,170});
	mScoreLabel->Position(400,Graphics::SCREEN_HEIGHT-30);
	mScoreLabel->Parent(this);

	mScoreboard = new Scoreboard({ 255,204,170 });
	mScoreboard->Position(510,Graphics::SCREEN_HEIGHT-30);
	mScoreboard->Parent(this);
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mLifeLabel;
	mLifeLabel = nullptr;

	for (auto ico : mLifeIcons) { // todo is this right?
		delete ico;
		ico = nullptr;
	}

	delete mScoreLabel;
	mScoreLabel = nullptr;

	delete mScoreboard;
	mScoreboard = nullptr;
}

void PlayScreen::Update() {
	mPlayer->Update();
}

void PlayScreen::Render() {
	//mPlayer->Render();
	mLifeLabel->Render();
	for (auto ico : mLifeIcons) {ico->Render();}
	mScoreLabel->Render();
	mScoreboard->Render();
}
