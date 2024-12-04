#pragma once
#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "BoxCollider.h"
#include "Bullet.h"

using namespace SDLFramework;

class Player : public PhysEntity {

public:

	Player();
	~Player();

	void Update() override;
	void Render() override;

	void Visible(bool visible);
	bool isAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	void wasHit();

	//inherited
	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;





private:

	static const int MAX_BULLETS = 2;
	Bullet* mBullets[MAX_BULLETS];

	bool mWasHit;

	Timer* mTimer;
	InputManager* mInputManager;
	AudioManager* mAudioManager;

	bool mVisible;
	bool mAnimating;

	Texture* mShip;
	AnimatedTexture* mDeathAnimation;

	int mScore;
	int mLives;

	float mMoveSpeed;
	Vector2 mMoveBounds;

	void HandleMovement();
	void HandleFiring();

};