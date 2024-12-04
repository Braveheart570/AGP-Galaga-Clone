#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudioManager = AudioManager::Instance();

	mBackgroundStars = BackgroundStars::Instance();

	mPlaySideBar = new PlaySideBar();
	mPlaySideBar->Parent(this);
	mPlaySideBar->Position(Graphics::SCREEN_WIDTH*0.87f, Graphics::SCREEN_HEIGHT*0.05f);

	mStartLabel = new Texture("START", "emulogic.ttf", 32, {150,0,0});
	mStartLabel->Parent(this);
	mStartLabel->Position(Graphics::SCREEN_WIDTH*0.4f,Graphics::SCREEN_HEIGHT*0.5f);

	mLevel = nullptr;
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;

	mPlayer = nullptr;

	Enemy::CreatePaths(); // must be called before enemy creation

}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudioManager = nullptr;

	mBackgroundStars = nullptr;

	delete mPlaySideBar;
	mPlaySideBar = nullptr;

	delete mLevel;
	mLevel = nullptr;

	delete mPlayer;
	mPlayer = nullptr;
}

void PlayScreen::Update() {
	
	if (mGameStarted) {
		if (!mLevelStarted) {
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay) {
				StartNextLevel();
			}
		}
		else {
			//the level has started or is in session.

			mLevel->Update();
			if (mLevel->State() == Level::Finished) {
				mLevelStarted = false;
			}
		}

		//we are in a level at this point
		if (mCurrentStage > 0) {
			mPlaySideBar->Update();
		}

		mPlayer->Update();

	}
	else {
		if (!Mix_PlayingMusic()) {
			//we have finnished playing intro music from start new game function.
			mGameStarted = true;
		}
	}

}


void PlayScreen::Render() {

	if (!mGameStarted) {
		mStartLabel->Render();
	}

	if (mGameStarted) {

		if (mLevelStarted) {
			mLevel->Render();
		}

		mPlayer->Render();
		
	}

	mPlaySideBar->Render();

}

void PlayScreen::StartNewGame() {

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.8f);
	mPlayer->Active(false);

	mPlaySideBar->SetHighScore(645987);
	mPlaySideBar->SetShips(mPlayer->Lives());
	mPlaySideBar->SetPlayerScore(mPlayer->Score());
	mPlaySideBar->SetLevel(0);


	mBackgroundStars->Scroll(false);
	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mCurrentStage = 0;
	//mAudioManager->PlayMusic("GameStart.wav", 0); //coment this out to skip music

}

void PlayScreen::StartNextLevel() {
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	delete mLevel;
	mLevel = new Level(mCurrentStage, mPlaySideBar, mPlayer);

}

bool PlayScreen::GameOver() {

	//if !mLevelStarted retunr false, otherwise return the value of the fallowing statement.
	return !mLevelStarted ? false : (mLevel->State() == Level::GameOver);

}