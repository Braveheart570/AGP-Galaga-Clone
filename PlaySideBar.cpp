#include "PlaySideBar.h"

PlaySideBar::PlaySideBar() {
	mTimer = Timer::Instance();
	mAudioManager = AudioManager::Instance();

	mBackground = new Texture("Black.png");
	mBackground->Parent(this);
	mBackground->Scale(Vector2(3.0f, 10.0f));
	mBackground->Position(45.0f, 380.0f);

	mHighLabel = new Texture("HIGH", "emulogic.ttf", 32, { 150,0,0 });
	mHighLabel->Parent(this);
	mHighLabel->Position(-25.0f, 0.0f);

	mScoreLabel = new Texture("SCORE", "emulogic.ttf", 32, {150,0,0});
	mScoreLabel->Parent(this);
	mScoreLabel->Position(25.0f,32.0f);

	mHighScoreBoard = new Scoreboard();
	mHighScoreBoard->Parent(this);
	mHighScoreBoard->Position(90.0f,64.0f);

	mOneUpLabel = new Texture("1UP", "emulogic.ttf", 32, { 150,0,0 });
	mOneUpLabel->Parent(this);
	mOneUpLabel->Position(-45.0f,160.0f);
	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mOneUpLabelVisible = true;

	mPlayerOneScore = new Scoreboard();
	mPlayerOneScore->Parent(this);
	mPlayerOneScore->Position(90.0f, 192.0f);

	mShips = new GameEntity();
	mShips->Parent(this);
	mShips->Position(-40.0f,420.0f);

	for (int c = 0; c < sMAX_SHIP_TEXTURES; c++) {
		mShipTextures[c] = new Texture("SpriteSheet.png",183,54,16,16);
		mShipTextures[c]->Parent(mShips);
		mShipTextures[c]->Scale(Vector2(3, 3));
		mShipTextures[c]->Position(62.0f * (c % 3), 60.0f * (c / 3));
	}

	mTotalShipsLabel = new Scoreboard();
	mTotalShipsLabel->Parent(mShips);
	mTotalShipsLabel->Position(124.0f, 60.0f);

	mFlags = new GameEntity();
	mFlags->Parent(this);
	mFlags->Position(-50.0f, 600.0f);

	mFlagTimer = 0.0f;
	mFlagInterval = 0.1f;


}

PlaySideBar::~PlaySideBar() {

	mTimer = nullptr;
	mAudioManager = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mHighLabel;
	mHighLabel = nullptr;

	delete mScoreLabel;
	mScoreLabel = nullptr;

	delete mHighScoreBoard;
	mHighScoreBoard = nullptr;

	delete mOneUpLabel;
	mOneUpLabel = nullptr;

	delete mPlayerOneScore;
	mPlayerOneScore = nullptr;

	delete mShips;
	mShips = nullptr;

	delete mTotalShipsLabel;
	mTotalShipsLabel = nullptr;

	for (int c = 0; c < sMAX_SHIP_TEXTURES; c++) {
		delete mShipTextures[c];
		mShipTextures[c] = nullptr;
	}

	delete mFlags;
	mFlags = nullptr;

	clearFlags();

}


void PlaySideBar::clearFlags() {

	for (int i = 0; i < mFlagTextures.size(); i++) {
		delete mFlagTextures[i];
		mFlagTextures[i] = nullptr;
	}

	mFlagTextures.clear();

}

void PlaySideBar::AddNextFlag() {

	if (mRemainingLevels >= 50) {
		AddFlag("levelFlags.png", 62, 50);
	}
	else if (mRemainingLevels >= 30) {
		AddFlag("levelFlags.png", 62, 30);
	}
	else if (mRemainingLevels >= 20) {
		AddFlag("levelFlags.png", 62, 20);
	}
	else if (mRemainingLevels >= 10) {
		AddFlag("levelFlags.png", 54, 10);
	}
	else if (mRemainingLevels >= 5) {
		AddFlag("levelFlags.png", 30, 5);
	}
	else{
		AddFlag("levelFlags.png", 30, 1);
	}
}

void PlaySideBar::AddFlag(std::string filename, float width, int value) {
	//gets the last element +1
	int index = (int)mFlagTextures.size();

	if (index > 0) {
		mFlagXOffset += width + 0.5f;
		
	}

	if (mFlagXOffset > 140) {
		mFlagYOffset += 66;
		mFlagXOffset = 0;
	}

	mRemainingLevels -= value;
	//the xposition we wnat to use to cut the flag from the texture.
	int x = 0;

	switch (value) {

	case 50:
		x = 228;
		break;
	case 30:
		x = 168;
		break;
	case 20:
		x = 108;
		break;
	case 10:
		x = 56;
		break;
	case 5:
		x = 28;
		break;

	}

	mFlagTextures.push_back(new Texture(filename, x, 0, width - 2, 64));
	mFlagTextures[index]->Parent(mFlags);
	mFlagTextures[index]->Position(mFlagXOffset, mFlagYOffset);
	mFlagXOffset += width * 0.5f;

	mAudioManager->PlaySFX("FlagSound.wav", 0, -1);

}

void PlaySideBar::SetLevel(int level) {

	clearFlags();
	mRemainingLevels = level;
	mFlagXOffset = 0.0f;

}


void PlaySideBar::Update(){

	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval) {
		mOneUpLabelVisible = !mOneUpLabelVisible;
		mBlinkTimer = 0.0f;
	}


	if (mRemainingLevels > 0) {
		mFlagTimer += mTimer->DeltaTime();

		if (mFlagTimer >= mFlagInterval) {
			AddNextFlag();
			mFlagTimer = 0.0f;
		}
	}


}

void PlaySideBar::Render(){

	mBackground->Render();
	mHighLabel->Render();
	mScoreLabel->Render();
	mHighScoreBoard->Render();
	mPlayerOneScore->Render();

	for (int c = 0; c < sMAX_SHIP_TEXTURES && c < mTotalShips; c++) {
		mShipTextures[c]->Render();
	}

	if (mTotalShips > sMAX_SHIP_TEXTURES) {

		mTotalShipsLabel->Render();

	}

	if (mOneUpLabelVisible) {
		mOneUpLabel->Render();
	}

	for (auto flag : mFlagTextures) {
		flag->Render();
	}

}

void PlaySideBar::SetShips(int ships) {
	mTotalShips = ships;
	if (ships > sMAX_SHIP_TEXTURES) {
		mTotalShipsLabel->Score(ships);
	}
}

void PlaySideBar::SetHighScore(int score) {
	mHighScoreBoard->Score(score);
}
void PlaySideBar::SetPlayerScore(int score) {
	mPlayerOneScore->Score(score);
}