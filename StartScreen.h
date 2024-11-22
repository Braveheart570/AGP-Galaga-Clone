#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {

public:

	StartScreen();

	~StartScreen();

	void Render() override;

	void Update() override;


private:

	Timer* mTimer;

	InputManager* mInputManager;

	//Empty GameEntity/objects
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mPlayerTwo;
	Texture* mHiScore;


	//logo entities
	GameEntity* mLogoHolder;
	Texture* mLogo;
	AnimatedTexture* mAnimatedLogo;

	//play mode entities
	GameEntity* mPlayModes;
	Texture* mOnePlayerMode;
	Texture* mTwoPlayerMode;
	Texture* mCursor;

	//Bottom bar entities
	GameEntity* mBottomBar;
	Texture* mNamco;
	Texture* mDates;
	Texture* mRights;


};