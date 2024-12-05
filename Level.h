#pragma once
#include "PlaySideBar.h"
#include "BackgroundStars.h"
#include "Player.h"
#include "Enemy.h"


class Level : public GameEntity {

public:

	enum LevelStates{Running, Finished, GameOver};

	LevelStates State();

	Level(int stage,PlaySideBar* sidebar, Player* player);
	~Level();

	void Update() override;
	void Render() override;

private:

	Timer* mTimer;
	PlaySideBar* mSideBar;
	BackgroundStars* mBackgroundStars;

	Player* mPlayer;

	int mStage;
	bool mStageStarted;

	Texture* mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Texture* mStageLabel;
	Scoreboard* mStageNumber;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	float mLabelTimer;

	bool mPlayerHit;
	float mRespawnDelay;
	float mRespawnTimer;
	float mRespawnLabelOnScreen;

	Texture* mGameOverLabel;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LevelStates mCurrentState;

	void HandleStartLabels();
	void HandleCollisions();
	void HandlePlayerDeath();

	void StartStage();
};