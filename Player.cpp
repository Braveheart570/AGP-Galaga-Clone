#include "Player.h"
#include "physicsManager.h"

void Player::HandleMovement() {


	if(mInputManager->KeyDown(SDL_SCANCODE_D)) {
		Translate(Vect2_Right*mMoveSpeed*mTimer->DeltaTime(), WORLD);
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_A)) {
		Translate(-Vect2_Right * mMoveSpeed * mTimer->DeltaTime(), WORLD);
	}

	Vector2 pos = Position(LOCAL);
	if (pos.x < mMoveBounds.x) {
		pos.x = mMoveBounds.x;
	}
	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.y;
	}

	Position(pos);

}

Player::Player() {

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 2;
	
	mMoveSpeed = 100.0f;
	mMoveBounds = Vector2(0.0f,800.0f);

	mShip = new Texture("SpriteSheet.png", 183, 54, 16, 16);
	mShip->Parent(this);
	mShip->Scale(Vector2(4,4));
	mShip->Position(Vect2_Zero);

	mDeathAnimation = new AnimatedTexture("PlayerExplosion.png", 0.0f, 0.0f, 128.0f, 128.0f, 4, 1.0f, AnimatedTexture::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vect2_Zero);
	mDeathAnimation->SetWrapMode(AnimatedTexture::Once);

	//Physics Entity
	AddCollider(new BoxCollider(Vector2(16,67)));
	AddCollider(new BoxCollider(Vector2(20, 37)),Vector2(18,10));
	AddCollider(new BoxCollider(Vector2(20, 37)), Vector2(-18, 10));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

}


Player::~Player() {

	mTimer = nullptr;
	mInputManager = nullptr;
	mAudioManager = nullptr;

	delete mShip;
	mShip = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

	//physics manager (or phys entity?) handles the colliders

}

void Player::Visible(bool visible) {

	mVisible = visible;

}

bool Player::isAnimating() {

	return mAnimating;

}

int Player::Score() {

	return mScore;

}
int Player::Lives() {

	return mLives;

}

void Player::AddScore(int change) {

	mScore += change;

}
// temp fucntion, will use hit in the future
void Player::wasHit() {
	mLives -= 1;
	mAnimating = true;
	mDeathAnimation->ResetAnimation();
	mAudioManager->PlaySFX("PlayerExplosion.wav");
}

bool Player::IgnoreCollisions() {

	return !mVisible || mAnimating;

}

void Player::Hit(PhysEntity* other) {

	mLives -= 1;
	mAnimating = true;
	mDeathAnimation->ResetAnimation();
	mWasHit = true;
	//todo audio

}

void Player::Update() {
	if (mAnimating) {
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	}
	else {
		if (Active()) {
			HandleMovement();
		}
		
	}

}

void Player::Render() {

	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else {
			mShip->Render();
		}

		PhysEntity::Render();

	}

}