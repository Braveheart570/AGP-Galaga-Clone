#pragma once
#include "Level.h"


class PlayScreen : public GameEntity {

public:

	PlayScreen();
	~PlayScreen();

	void StartNewGame();
	void StartNextLevel();

	void Update() override;
	void Render() override;

private:

	Timer* mTimer;
	AudioManager* mAudioManager;

	BackgroundStars* mBackgroundStars;

	PlaySideBar* mPlaySideBar;



	Texture* mStartLabel;

	Level* mLevel;

	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;
	bool mLevelStarted;
	int mCurrentStage;

};