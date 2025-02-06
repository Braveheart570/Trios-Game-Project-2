#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Player.h"
#include "UIBar.h"
#include "LifeIcon.h"
#include "Level.h"
#include "HeartManager.h"

class PlayScreen : public GameEntity {


public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;

	bool GameOver();

	bool Win();

private:
	Timer* mTimer;
	AudioManager* mAudio;

	HeartManager* mHeartManager;

	Player* mPlayer;
	Vector2 mPlayerSpawn;

	GLTexture* mControls;
	GLTexture* MChamberNumLabel;

	bool mStarted;
	float mIntroTime;
	float mIntroDur;

	bool mLevelCompleted;
	float LevelTransitionTime;
	float LevelTransitionDur;
	GLTexture* mLevelClearedLabel;

	GLTexture* mGameOverTex;

	bool mWin;

	static const int sTotalLevelCount = 8;
	Level* mLevels[sTotalLevelCount];
	int mLevelIndex;

	Level* mCurrentlevel;

	UIBar* mUIBar;

	void NextLevel();
};
#endif