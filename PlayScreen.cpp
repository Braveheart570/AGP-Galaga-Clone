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