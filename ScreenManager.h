#pragma once
#include "StartScreen.h"
#include "PlayScreen.h"
#include "BackgroundStars.h"
#include <iostream>

class ScreenManager {

public:

	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:

	enum Screens {Start, Play};
	Screens mCurrentScreen;

	static ScreenManager* sInstance;

	BackgroundStars* mBackgroundStars;
	InputManager* mInputManager;

	//screens
	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;

	ScreenManager();
	~ScreenManager();

};