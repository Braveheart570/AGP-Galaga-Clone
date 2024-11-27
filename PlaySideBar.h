#pragma once
#include "Timer.h"
#include "ScoreBoard.h"
#include "AudioManager.h"

using namespace SDLFramework;

class PlaySideBar : public GameEntity {

public:

	PlaySideBar();
	~PlaySideBar();

	void Update() override;
	void Render() override;


private:
	Timer* mTimer;
	AudioManager* mAudioManager;

	Texture* mBackground;

	Texture* mHighLabel;
	Texture* mScoreLabel;
	Scoreboard* mHighScoreBoard;

};