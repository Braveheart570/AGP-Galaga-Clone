#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudioManager = AudioManager::Instance();

	mBackgroundStars = BackgroundStars::Instance();

	mPlaySideBar = new PlaySideBar();
	mPlaySideBar->Parent(this);
	mPlaySideBar->Position(Graphics::SCREEN_WIDTH*0.87f, Graphics::SCREEN_HEIGHT*0.05f);
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudioManager = nullptr;
	mBackgroundStars = nullptr;

}

void PlayScreen::Update() {

	mPlaySideBar->Update();

}


void PlayScreen::Render() {

	mPlaySideBar->Render();

}

void PlayScreen::StartNewGame() {

	mPlaySideBar->SetHighScore(645987);
	mPlaySideBar->SetPlayerScore(0);
	mPlaySideBar->SetShips(6);
	//testing
	StartNextLevel();
}

void PlayScreen::StartNextLevel() {
	mPlaySideBar->SetLevel(75);
}