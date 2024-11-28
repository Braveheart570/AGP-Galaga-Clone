#pragma once
#include "Timer.h"
#include "ScoreBoard.h"
#include "AudioManager.h"

using namespace SDLFramework;

class PlaySideBar : public GameEntity {

public:

	PlaySideBar();
	~PlaySideBar();

	void SetShips(int ships);
	void SetPlayerScore(int score);
	void SetHighScore(int score);

	void SetLevel(int level);

	void Update() override;
	void Render() override;


private:
	static const int sMAX_SHIP_TEXTURES = 5;


	Timer* mTimer;
	AudioManager* mAudioManager;

	Texture* mBackground;

	Texture* mHighLabel;
	Texture* mScoreLabel;
	Scoreboard* mHighScoreBoard;

	Texture* mOneUpLabel;
	float mBlinkTimer;
	float mBlinkInterval;
	bool mOneUpLabelVisible;

	Scoreboard* mPlayerOneScore;

	GameEntity* mShips;
	Texture* mShipTextures[sMAX_SHIP_TEXTURES];
	Scoreboard* mTotalShipsLabel;
	int mTotalShips;

	GameEntity* mFlags;
	std::vector<Texture*> mFlagTextures;
	int mRemainingLevels;

	float mFlagXOffset;
	float mFlagYOffset;
	float mFlagTimer;
	float mFlagInterval;

	void clearFlags();
	void AddNextFlag();
	void AddFlag(std::string filename, float width, int value);


};