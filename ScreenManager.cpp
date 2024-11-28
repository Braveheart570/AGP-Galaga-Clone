#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}
	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager() {
	mBackgroundStars = BackgroundStars::Instance();
	mInputManager = InputManager::Instance();
	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
	mCurrentScreen = Start;
}

ScreenManager::~ScreenManager() {
	
	BackgroundStars::Release();
	mBackgroundStars = nullptr;

	mInputManager = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;
}

void ScreenManager::Update() {
	mBackgroundStars->Update();

	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Update();

		if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN)) {
			mCurrentScreen = Play;
			mStartScreen->ResetAnimation();
			mPlayScreen->StartNewGame();
			
		}

		break;
	case Play:

		mPlayScreen->Update();

		if (mInputManager->KeyPressed(SDL_SCANCODE_ESCAPE)) {
			mCurrentScreen = Start;
			
		}

		break;
	default:
		std::cerr << "Invalad screen type in ScreenManager." << std::endl;
	}

}

void ScreenManager::Render() {

	mBackgroundStars->Render();

	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Render();
		break;
	case Play:
		mPlayScreen->Render();
		break;
	}


}