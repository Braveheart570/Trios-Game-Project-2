#include "UIBar.h"

UIBar::UIBar(Player* player) {

	//todo the position of the uibar is technically zero, might be good to correct relative positions

	mPlayer = player;

	mKnownScore = mPlayer->Score();

	mLifeLabel = new GLTexture("life:", "pico-8-mono-upper.ttf", 20, { 255,204,170 });
	mLifeLabel->Position({ 60,Graphics::SCREEN_HEIGHT - 30 });
	mLifeLabel->Parent(this);

	for (int c = 0; c < mPlayer->MaxHeath(); c++) {
		mLifeIcons.push_back(new LifeIcon(110 + (c * 15), Graphics::SCREEN_HEIGHT - 30));
		mLifeIcons[c]->Parent(this);
	}
	mDisplayedHealth = mPlayer->MaxHeath();

	mScoreLabel = new GLTexture("score:", "pico-8-mono-upper.ttf", 20, { 255,204,170 });
	mScoreLabel->Position(400, Graphics::SCREEN_HEIGHT - 30);
	mScoreLabel->Parent(this);

	mScoreboard = new Scoreboard({ 255,204,170 });
	mScoreboard->Position(600, Graphics::SCREEN_HEIGHT - 30);
	mScoreboard->Parent(this);

}

UIBar::~UIBar() {
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

void UIBar::Render() {

	mLifeLabel->Render();
	for (auto ico : mLifeIcons) { ico->Render(); }
	mScoreLabel->Render();
	mScoreboard->Render();

}

void UIBar::Update() {

	if (mPlayer->Score() != mKnownScore) {
		mKnownScore = mPlayer->Score();
		mScoreboard->Score(mKnownScore);
	}


	if (mPlayer->Health() != mDisplayedHealth) {
		mDisplayedHealth = mPlayer->Health();

		for (int c = 0; c < mLifeIcons.size(); c++) {
			if (c < mDisplayedHealth) {
				mLifeIcons[c]->Active(true);
			}
			else {
				mLifeIcons[c]->Active(false);
			}
		}
	}

	

}