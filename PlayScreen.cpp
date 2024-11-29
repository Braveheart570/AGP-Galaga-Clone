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

}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudioManager = nullptr;

	mBackgroundStars = nullptr;

	delete mPlaySideBar;
	mPlaySideBar = nullptr;

	delete mLevel;
	mLevel = nullptr;


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
		}

		//we are in a level at this point
		if (mCurrentStage > 0) {
			mPlaySideBar->Update();
		}


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

	if (mGameStarted && mLevelStarted) {
		mLevel->Render();
	}

	mPlaySideBar->Render();

}

void PlayScreen::StartNewGame() {

	mPlaySideBar->SetHighScore(645987);
	mPlaySideBar->SetShips(2);
	mBackgroundStars->Scroll(false);
	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mCurrentStage = 0;
	mAudioManager->PlayMusic("GameStart.wav", 0);

}

void PlayScreen::StartNextLevel() {
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	delete mLevel;
	mLevel = new Level(mCurrentStage, mPlaySideBar);

}