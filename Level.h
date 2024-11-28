#pragma once
#include "PlaySideBar.h"
#include "BackgroundStars.h"



class Level : public GameEntity {

public:

	Level(int stage,PlaySideBar* sidebar);
	~Level();

	void Update() override;
	void Render() override;

private:

	Timer* mTimer;
	PlaySideBar* mSidebar;
	BackgroundStars* mBackgroundStars;

	int mStage;
	bool mStageStarted;

	Texture* mReadylabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Texture* mStageLabel;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	float labelTimer;

	void StartStage();
};