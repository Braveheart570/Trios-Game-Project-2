#include "WinScreen.h"

WinScreen::WinScreen() {
	mTimer = Timer::Instance();

	mBackground = new ScrollingBG();
	mBackground->Parent(this);
	mBackground->ResetAnimations();

	mText1 = new GLTexture("Evil has been defeated", "pico-8-mono-upper.ttf", 20, { 255,204,170 });
	mText1->Position({Graphics::SCREEN_WIDTH/2,160});
	mText1->Parent(this);

	mText2 = new GLTexture("The people are safe", "pico-8-mono-upper.ttf", 20, { 255,204,170 });
	mText2->Position({ Graphics::SCREEN_WIDTH / 2,210 });
	mText2->Parent(this);

	mText3 = new GLTexture("Thanks for playing!", "pico-8-mono-upper.ttf", 20, { 255,204,170 });
	mText3->Position({ Graphics::SCREEN_WIDTH / 2,500 });
	mText3->Parent(this);

	mText4 = new GLTexture("Press X to reset", "pico-8-mono-upper.ttf", 20, { 255,204,170 });
	mText4->Position({ Graphics::SCREEN_WIDTH / 2,550 });
	mText4->Parent(this);

}

WinScreen::~WinScreen() {
	mTimer = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mText1;
	mText1 = nullptr;

	delete mText2;
	mText2 = nullptr;

	delete mText3;
	mText3 = nullptr;

	delete mText4;
	mText4 = nullptr;
}

void WinScreen::Update() {
	mBackground->Update();
}

void WinScreen::Render() {
	mBackground->Render();
	mText1->Render();
	mText2->Render();
	mText3->Render();
	mText4->Render();
}