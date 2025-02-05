#pragma once
#include "LifeIcon.h"
#include "Scoreboard.h"
#include "Player.h"

using namespace SDLFramework;

class UIBar : public GameEntity {

public:

	UIBar(Player* player);
	~UIBar();

	void Render() override;
	void Update() override;

private:

	GLTexture* mLifeLabel;
	std::vector<LifeIcon*> mLifeIcons;

	int mDisplayedHealth;
	int mKnownScore;
	int mKnownMaxHealth;

	GLTexture* mScoreLabel;
	Scoreboard* mScoreboard;

	Player* mPlayer;

};