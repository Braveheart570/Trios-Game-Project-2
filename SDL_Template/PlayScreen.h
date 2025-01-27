#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Player.h"
#include "UIBar.h"
#include "LifeIcon.h"
#include "Level.h"

class PlayScreen : public GameEntity {


public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;

	void Reset();


private:
	Timer* mTimer;
	AudioManager* mAudio;

	Player* mPlayer;

	static const int sTotalLevelCount = 16;
	Level* mLevels[sTotalLevelCount];

	Level* mCurrentlevel;

	UIBar* mUIBar;
};
#endif