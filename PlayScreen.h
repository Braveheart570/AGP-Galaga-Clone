#pragma once
#include "BackgroundStars.h"
#include "PlaySideBar.h"


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


};