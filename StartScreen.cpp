#include "StartScreen.h"



StartScreen::StartScreen() {

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();

	//cursor variables
	mSelectedMode = 0;
	mCursorStartPosition = Vector2(-175.0f, -35.0f);
	mCursorOffsetPos = Vector2(0,70.0f);


	//top bar
	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH*0.5f, 80.0f);

	mPlayerOne = new Texture("1UP", "emulogic.ttf", 32, { 200,0,0 });
	mPlayerTwo = new Texture("2UP", "emulogic.ttf", 32, { 200,0,0 });
	mHiScore = new Texture("HI SCORE", "emulogic.ttf", 32, { 200,0,0 });

	mTopBar->Parent(this);
	mPlayerOne->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mHiScore->Parent(mTopBar);

	mPlayerOne->Position(-Graphics::SCREEN_WIDTH * 0.35, 0);
	mPlayerTwo->Position(Graphics::SCREEN_WIDTH * 0.2, 0);
	mHiScore->Position(-30, 0.0f);

	mPlayerOneScore = new Scoreboard();
	mPlayerTwoScore = new Scoreboard();
	mHighScore = new Scoreboard();

	mPlayerOneScore->Parent(mTopBar);
	mPlayerTwoScore->Parent(mTopBar);
	mHighScore->Parent(mTopBar);

	mPlayerOneScore->Position(-Graphics::SCREEN_WIDTH * 0.23f, 40.0f);
	mPlayerTwoScore->Position(Graphics::SCREEN_WIDTH * 0.32f, 40.0f);
	mHighScore->Position(Graphics::SCREEN_WIDTH*0.05f, 40.0f);

	mHighScore->Score(80); // this is screwing up other scoreboards.


	//logo and holder
	mLogoHolder = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);
	mLogo = new Texture("GalagaLogo.png", 0,0,360,180);

	mLogoHolder->Parent(this);
	mLogo->Parent(mLogoHolder);

	mLogo->Position(Vect2_Zero);

	//animated logo
	mAnimatedLogo = new AnimatedTexture("GalagaLogo.png", 0, 0, 360, 180, 3, 0.3f, AnimatedTexture::Vertical);
	mAnimatedLogo->Parent(mLogoHolder);
	mAnimatedLogo->Position(Vect2_Zero);


	//ply modes menu
	mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH*0.5, Graphics::SCREEN_HEIGHT*0.55f);
	mOnePlayerMode = new Texture("1 Player", "emulogic.ttf", 32, { 230,230,230 });
	mTwoPlayerMode = new Texture("2 Player", "emulogic.ttf", 32, { 230,230,230 });
	mCursor = new Texture("Cursor.png");

	mPlayModes->Parent(this);
	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	mOnePlayerMode->Position(0.0f, -35.0f);
	mTwoPlayerMode->Position(0.0f, 35.0f);
	mCursor->Position(mCursorStartPosition);


	//bottom bar
	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
	mNamco = new Texture("namco", "namco__.ttf", 36, {200,0,0});
	mDates = new Texture("1981 1985 NAMCO LTD.", "emulogic.ttf", 32, { 230,230,230 });
	mRights = new Texture("ALL RIGHTS RESERVED", "emulogic.ttf", 32, { 230,230,230 });

	mBottomBar->Parent(this);
	mNamco->Parent(mBottomBar);
	mDates->Parent(mBottomBar);
	mRights->Parent(mBottomBar);

	mNamco->Position(Vect2_Zero);
	mDates->Position(0.0f,90.0f);
	mRights->Position(0.0f, 170.0f);


	//screen animation init
	ResetAnimation();

}


StartScreen::~StartScreen() {

	delete mTopBar;
	mTopBar = nullptr;

	delete mPlayerOne;
	mPlayerOne = nullptr;

	delete mPlayerTwo;
	mPlayerTwo = nullptr;

	delete mHiScore;
	mHiScore = nullptr;

	delete mPlayerOneScore;
	mPlayerOneScore = nullptr;

	delete mPlayerTwoScore;
	mPlayerTwoScore = nullptr;

	delete mHighScore;
	mHighScore = nullptr;


	delete mLogoHolder;
	mLogoHolder = nullptr;

	delete mLogo;
	mLogo = nullptr;

	delete mAnimatedLogo;
	mAnimatedLogo = nullptr;



	delete mPlayModes;
	mPlayModes = nullptr;

	delete mOnePlayerMode;
	mOnePlayerMode = nullptr;

	delete mTwoPlayerMode;
	mTwoPlayerMode = nullptr;

	delete mCursor;
	mCursor = nullptr;


	
	delete mBottomBar;
	mBottomBar = nullptr;

	delete mNamco;
	mNamco = nullptr;

	delete mDates;
	mDates = nullptr;

	delete mDates;
	mDates = nullptr;

	delete mRights;
	mRights = nullptr;




	mTimer = nullptr;

	mInputManager = nullptr;

}

void StartScreen::Render() {

	mPlayerOne->Render();
	mPlayerTwo->Render();
	mHiScore->Render();

	mPlayerOneScore->Render();
	mPlayerTwoScore->Render();
	mHighScore->Render();

	if (mAnimationDone) {
		mAnimatedLogo->Render();
	}
	else {
		mLogo->Render();
	}
	

	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();
	mCursor->Render();

	mNamco->Render();
	mDates->Render();
	mRights->Render();


}

void StartScreen::Update() {

	if (!mAnimationDone) {

		mAnimationTimer += mTimer->DeltaTime();
		Position(lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime) {
			mAnimationDone = true;

			
		}

		if (mInputManager->KeyPressed(SDL_SCANCODE_SPACE)) {
			mAnimationTimer = mAnimationTotalTime;
		}


	}
	else {
		mAnimatedLogo->Update();

		//input
		if (mInputManager->KeyPressed(SDL_SCANCODE_S)) {
			ChangeSelectedMode(1);
		}
		else if(mInputManager->KeyPressed(SDL_SCANCODE_W)) {
			ChangeSelectedMode(-1);
		}
		else if (mInputManager->KeyPressed(SDL_SCANCODE_SPACE)) {

		}
		else if (mInputManager->KeyPressed(SDL_SCANCODE_X)) { // testing
			mHighScore->Score(8700); // this is screwing up other scoreboards.TODO
		}

	}


}



void StartScreen::ChangeSelectedMode(int change) {

	mSelectedMode += change;
	if (mSelectedMode > 1) {
		mSelectedMode = 0;
	}
	else if (mSelectedMode < 0) {
		mSelectedMode = 1;
	}

	mCursor->Position(mCursorStartPosition + (mCursorOffsetPos * (float)mSelectedMode));
	

}

void StartScreen::ResetAnimation() {
	mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mAnimationEndPos = Vect2_Zero;
	mAnimationTotalTime = 5.0f;
	mAnimationDone = false;
	mAnimationTimer = 0;
	Position(mAnimationStartPos);
}

int StartScreen::selectedMode() {
	return mSelectedMode;
}