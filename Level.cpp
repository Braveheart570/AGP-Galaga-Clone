#include "Level.h"

void Level::StartStage() {

	mStageStarted = true;

}

Level::Level(int stage, PlaySideBar* sidebar, Player* player) {

	mTimer = Timer::Instance();
	mSideBar = sidebar;
	mSideBar->SetLevel(stage);
	mBackgroundStars = BackgroundStars::Instance();

	mPlayer = player;

	mStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;

	mStageLabel = new Texture("STAGE", "emulogic.ttf", 32, {75,75,200});
	mStageLabel->Parent(this);
	mStageLabel->Position(Graphics::SCREEN_WIDTH*0.35f,Graphics::SCREEN_HEIGHT*0.5f);

	mStageNumber = new Scoreboard({ 75, 75, 200 });
	mStageNumber->Score(stage);
	mStageNumber->Parent(this);
	mStageNumber->Position(Graphics::SCREEN_WIDTH*0.5f,Graphics::SCREEN_HEIGHT*0.5f);

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.5f;

	mReadyLabel = new Texture("READY", "emulogic.ttf", 32, {150,0,0});
	mReadyLabel->Parent(this);
	mReadyLabel->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 3.0f;

	mPlayerHit = false;
	mRespawnDelay = 3.0f;
	mRespawnLabelOnScreen = 2.0f;

	mGameOverLabel = new Texture("GAME OVER!", "emulogic.ttf", 32, { 150,0,0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);

	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = Running;

	mFormation = new Formation();
	mFormation->Position(Graphics::SCREEN_WIDTH*0.4f,150.0f);
	Enemy::SetFormation(mFormation);

}

Level::~Level() {

	mTimer = nullptr;
	mSideBar = nullptr;
	mBackgroundStars = nullptr;

	mPlayer = nullptr;

	delete mStageLabel;
	mStageLabel = nullptr;

	delete mStageNumber;
	mStageNumber = nullptr;

	delete mReadyLabel;
	mReadyLabel = nullptr;

	delete mGameOverLabel;
	mGameOverLabel = nullptr;

	mPlayer = nullptr;

	delete mFormation;
	mFormation = nullptr;

	for (auto e : mEnemies) {
		delete e;
		e = nullptr;
	}
	mEnemies.clear();

}

Level::LevelStates Level::State() {

	return mCurrentState;

}

void Level::HandleStartLabels() {

	mLabelTimer += mTimer->DeltaTime();

	if (mLabelTimer >= mStageLabelOffScreen) {

		mBackgroundStars->Scroll(true);
		mPlayer->Active(true);
		mPlayer->Visible(true);


		if (mStage > 1) {
			StartStage();
		}
		else {
			//ready label will only show at start of level one
			if (mLabelTimer >= mReadyLabelOffScreen) {
				StartStage();
			}
		}
	}

}

void Level::HandleCollisions() {

	if (!mPlayerHit) {
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_X)) {
			mPlayer->wasHit();
			mSideBar->SetShips(mPlayer->Lives());

			mPlayerHit = true;
			mRespawnTimer = 0.0f;
			mPlayer->Active(false);
			mBackgroundStars->Scroll(false);
		}
	}

}
		
void Level::HandlePlayerDeath() {
	if (!mPlayer->isAnimating()) {
		if (mPlayer->Lives() > 0) {
			if (mRespawnTimer == 0.0f) {
				//the player has finished their death animation
				//hide untill respawn timer has finnished
				mPlayer->Visible(false);
			}

			mRespawnTimer += mTimer->DeltaTime();

			if (mRespawnTimer >= mRespawnDelay) {
				//this is where we respawn the player

				mPlayer->Active(true);
				mPlayer->Visible(true);
				mPlayerHit = false;
				mBackgroundStars->Scroll(true);


			}
		}
		else {
			//this is game over
			if (mGameOverTimer == 0.0f) {
				mPlayer->Visible(false);
			}

			mGameOverTimer += mTimer->DeltaTime();
			if (mGameOverTimer >= mGameOverDelay) {
				mCurrentState = GameOver;
			}

		}
	}

}

void Level::HandleEnemySpawning() {

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_S) && mButterflyCount < MAX_BUTTERFLYS) {
		mEnemies.push_back(new Butterfly(0,mButterflyCount++, false));
	}

}

void Level::HandleEnemyFormation() {

	mFormation->Update();

	if (mButterflyCount == MAX_BUTTERFLYS) {
		bool flyIn = false;
		for(auto enemy : mEnemies) {
			if (enemy->CurrentState() == Enemy::FlyIn) {
				flyIn = false;
				break;
			}
		}

		if (!flyIn) {
			mFormation->Lock();
		}

	}

}


void Level::HandleEnemyDiving() {}


void Level::Update() {

	if (mStageStarted == false) {

		HandleStartLabels();

	}
	else {

		HandleEnemySpawning();
		HandleEnemyFormation();
		HandleEnemyDiving();

		for (auto e : mEnemies) {
			e->Update();
		}


		HandleCollisions();

		if (mPlayerHit) {
			HandlePlayerDeath();
		}
		else {
			//TODO temp logic
			if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N)) {
				mCurrentState = Finished;
			}
		}
	}
}

void Level::Render() {

	if (mStageStarted == false) {
		if (mLabelTimer > mStageLabelOnScreen && mLabelTimer < mStageLabelOffScreen) {
			mStageLabel->Render();
			mStageNumber->Render();
		}
		else if(mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen) {
			mReadyLabel->Render();
		}
	}
	else {

		for (auto e : mEnemies) {
			e->Render();
		}

		if (mPlayerHit) {
			if (mRespawnTimer >= mRespawnLabelOnScreen) {
				mReadyLabel->Render();
			}

			if (mGameOverTimer >= mGameOverLabelOnScreen) {
				mGameOverLabel->Render();
			}
		}
	}

}