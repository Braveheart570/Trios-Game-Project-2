#pragma once
#include "LifeIcon.h"
#include "Scoreboard.h"

using namespace SDLFramework;

class UIBar : public GameEntity {

public:

	UIBar();
	~UIBar();

	void Render() override;
	void Update() override;

private:

	GLTexture* mLifeLabel;
	std::vector<LifeIcon*> mLifeIcons;

	GLTexture* mScoreLabel;
	Scoreboard* mScoreboard;

};