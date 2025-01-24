#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Player.h"
#include "Scoreboard.h"
#include "LifeIcon.h"

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	AudioManager * mAudio;

	Player * mPlayer;

	GLTexture* mLifeLabel;
	std::vector<LifeIcon*> mLifeIcons;

	GLTexture* mScoreLabel;
	Scoreboard* mScoreboard;



public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;
};
#endif