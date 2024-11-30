#pragma once
#include "Level.h"
#include "Player.h"



class PlayScreen : public GameEntity {

public:

	PlayScreen();
	~PlayScreen();

	void StartNewGame();
	void StartNextLevel();

	bool GameOver();

	void Update() override;
	void Render() override;

private:

	Timer* mTimer;
	AudioManager* mAudioManager;

	BackgroundStars* mBackgroundStars;

	PlaySideBar* mPlaySideBar;



	Texture* mStartLabel;

	Player* mPlayer;

	Level* mLevel;

	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;
	bool mLevelStarted;
	int mCurrentStage;

};