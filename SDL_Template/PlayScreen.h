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

	bool GameOver();

private:
	Timer* mTimer;
	AudioManager* mAudio;

	Player* mPlayer;
	Vector2 mPlayerSpawn;

	static const int sTotalLevelCount = 16;
	Level* mLevels[sTotalLevelCount];
	int mLevelIndex;

	Level* mCurrentlevel;

	UIBar* mUIBar;

	void NextLevel();
};
#endif