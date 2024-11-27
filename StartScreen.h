#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "Scoreboard.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {

public:

	StartScreen();

	~StartScreen();

	void Render() override;

	void Update() override;

	void ChangeSelectedMode(int change);

	void ResetAnimation();

	int selectedMode();


private:

	Timer* mTimer;

	InputManager* mInputManager;

	//Screen animation
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;


	//Top Bar entities
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mPlayerTwo;
	Texture* mHiScore;
	Scoreboard* mPlayerOneScore;
	Scoreboard* mPlayerTwoScore;
	Scoreboard* mHighScore;


	//logo entities
	GameEntity* mLogoHolder;
	Texture* mLogo;
	AnimatedTexture* mAnimatedLogo;

	//play mode entities
	GameEntity* mPlayModes;
	Texture* mOnePlayerMode;
	Texture* mTwoPlayerMode;
	Texture* mCursor;
	//Cursor
	Vector2 mCursorStartPosition;
	Vector2 mCursorOffsetPos;
	int mSelectedMode;

	//Bottom bar entities
	GameEntity* mBottomBar;
	Texture* mNamco;
	Texture* mDates;
	Texture* mRights;


};