#pragma once
#include "PlaySideBar.h"
#include "BackgroundStars.h"
#include "Player.h"
#include "Butterfly.h"
#include "Wasp.h"
#include "Boss.h"
#include "tinyxml2.h"

using namespace tinyxml2;


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
	Formation* mFormation;

	static const int MAX_BUTTERFLYS = 16;
	static const int MAX_WASPS = 20;
	static const int MAX_BOSSES = 4;

	int mButterflyCount;
	int mWaspCount;
	int mBossCount;

	Butterfly* mFormationButterfly[MAX_BUTTERFLYS];
	Wasp* mFormationWasp[MAX_WASPS];
	Boss* mFormationBoss[MAX_BOSSES];

	std::vector<Enemy*> mEnemies;

	XMLDocument mSpawningPatterns; 
	int mCurrentFlyinPriority;
	int mCurrentFlyInIndex;

	float mSpawnDelay;
	float mSpawnTimer;
	bool mSpawningFinished;

	int mStage;
	bool mChallengeStage;
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

	bool EnemyFlyingIn();

	void HandleEnemySpawning();
	void HandleEnemyFormation();
	void HandleEnemyDiving();
};