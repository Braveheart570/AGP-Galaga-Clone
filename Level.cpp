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
	
	mButterflyCount = 0;
	mWaspCount = 0;
	mBossCount = 0;

	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Data/Level1.xml");
	mSpawningPatterns.LoadFile(fullPath.c_str());

	mChallengeStage = mSpawningPatterns.FirstChildElement("Level")->FirstChildElement()->BoolAttribute("value");

	if (!mChallengeStage) {
		mFormation = new Formation();
		mFormation->Position(Graphics::SCREEN_WIDTH * 0.4f, 150.0f);
		Enemy::SetFormation(mFormation);
		
		for (int i = 0; i < MAX_BUTTERFLYS; i++) {
			mFormationButterfly[i] = nullptr;
		}
		for (int i = 0; i < MAX_WASPS; i++) {
			mFormationWasp[i] = nullptr;
		}
		for (int i = 0; i < MAX_BOSSES; i++) {
			mFormationBoss[i] = nullptr;
		}

	}

	mCurrentFlyinPriority = 0;
	mCurrentFlyInIndex = 0;
	mSpawnDelay = 0.2f;
	mSpawnTimer = 0.0f;
	mSpawningFinished = false;

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

	for (int i = 0; i < MAX_BUTTERFLYS; i++) {
		delete mFormationButterfly[i];
		mFormationButterfly[i] = nullptr;
	}
	for (int i = 0; i < MAX_WASPS; i++) {
		delete mFormationWasp[i];
		mFormationWasp[i] = nullptr;
	}
	for (int i = 0; i < MAX_BOSSES; i++) {
		delete mFormationWasp[i];
		mFormationBoss[i] = nullptr;
	}

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

	/*
	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_S) && mButterflyCount < MAX_BUTTERFLYS) {
		mEnemies.push_back(new Butterfly(0,mButterflyCount++, false));
	}

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_W) && mWaspCount < MAX_WASPS) {
		mEnemies.push_back(new Wasp(0, mWaspCount++, false, false));
	}

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_F) && mBossCount < MAX_BOSSES) {
		mEnemies.push_back(new Boss(0, mBossCount++, false));
	}
	*/


	mSpawnTimer += mTimer->DeltaTime();

	if (mSpawnTimer >= mSpawnDelay) {
		XMLElement* element = mSpawningPatterns.FirstChildElement("Level")->FirstChild()->NextSiblingElement();
		bool spawned = false;
		bool priorityFound = false;

		while (element != nullptr) {

			int priority = element->IntAttribute("priority");

			if (mCurrentFlyinPriority == priority) {
				priorityFound = true;
				int path = element->IntAttribute("path");
				XMLElement* child = element->FirstChildElement();

				//this for loop is always going to give us the next/last child based on our flyInIndex.
				for (int i = 0; i < mCurrentFlyInIndex && child != nullptr; i++) {
					child = child->NextSiblingElement();
				}

				if (child != nullptr) {
					std::string type = child->Attribute("type");
					int index = child->IntAttribute("index");

					if (type.compare("Butterfly") == 0) {
						if (!mChallengeStage) {
							//add butterfly to formation
							mFormationButterfly[index] = new Butterfly(path, index, false);
						}
						else {
							//todo: change chalange bool to true once challenge is implemented
							mEnemies.push_back(new Butterfly(path, index, false));
						}
					}

					spawned = true;
				}

			}

			element = element->NextSiblingElement();
		}

		if (!priorityFound) {
			//no priorities found = no more spawn elements.
			mSpawningFinished = true;
		}
		else {
			if (!spawned) {
				//we have spawn elements waiting but we didn't spawn anything
				if (!EnemyFlyingIn()) {
					mCurrentFlyinPriority++;
					mCurrentFlyInIndex = 0;
				}
			}
			else {
				// we haven't finished spawning our element's enemies
				mCurrentFlyInIndex++;
			}
		}

		mSpawnTimer = 0.0f;

	}
}


bool Level::EnemyFlyingIn() {
	for (Butterfly* butterfly : mFormationButterfly) {
		if (butterfly!= nullptr && butterfly->CurrentState() == Enemy::FlyIn) {
			return true;
		}
	}

	return false;
}


void Level::HandleEnemyFormation() {

	mFormation->Update();

	if (mButterflyCount == MAX_BUTTERFLYS && mWaspCount == MAX_WASPS && mBossCount == MAX_BOSSES) {
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


void Level::HandleEnemyDiving() {

	if (mFormation->Locked()) {

		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_V)) {
			for (auto enemy : mEnemies) {
				if (enemy->Type() == Enemy::Wasp && enemy->CurrentState() == Enemy::InFormation) {
					enemy->Dive();
					break;
				}
			}
		}

		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_B)) {
			for (auto enemy : mEnemies) {
				if (enemy->Type() == Enemy::Butterfly && enemy->CurrentState() == Enemy::InFormation) {
					enemy->Dive();
					break;
				}
			}
		}

		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_H)) {
			for (auto enemy : mEnemies) {
				if (enemy->Type() == Enemy::Boss && enemy->CurrentState() == Enemy::InFormation) {
					enemy->Dive();

					int index = enemy->Index();
					int firstEscortIndex = (index % 2 == 0) ? (index * 2) : (index * 2 - 1);
					int secondEscortIndex = firstEscortIndex + 4;

					for (auto butterfly : mEnemies) {
						if (butterfly->Type() == Enemy::Butterfly && 
							butterfly->CurrentState() == Enemy::InFormation && 
							(butterfly->Index() == firstEscortIndex || butterfly->Index() == secondEscortIndex)) {

							butterfly->Dive(1);

						}
					}

					break;
				}
			}
		}



	}

}


void Level::Update() {

	if (mStageStarted == false) {

		HandleStartLabels();

	}
	else {

		if (!mSpawningFinished) {
			HandleEnemySpawning();
		}
		if (!mChallengeStage) {
			HandleEnemyFormation();
		}
		else {
			for (auto e : mEnemies) {
				e->Update();
			}
		}

		HandleEnemyDiving();

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