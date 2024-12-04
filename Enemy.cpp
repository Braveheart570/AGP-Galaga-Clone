#include "Enemy.h"

std::vector<std::vector<Vector2>> Enemy::sPaths;

Player* Enemy::sPlayer = nullptr;



void Enemy::CreatePaths() {

	int screenMidPoint = (int)(Graphics::Instance()->SCREEN_WIDTH * 0.4f);

	int currentPath = 0;

	BezierPath* path = new BezierPath();

	path->AddCurve({Vector2(500.0f,10.0f),Vector2(500.0f,0.0f),Vector2(500.0f,310.0f),Vector2(500.0f,300.0f) }, 1);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
}


Enemy::Enemy(int path) : mCurrentPath(path) {

	mTimer = Timer::Instance();

	mCurrentState = FlyIn;

	mCurrentWaypoint = 1;

	Position(sPaths[mCurrentPath][0]);

	mTexture = new Texture("AnimatedEnemies.png", 0, 0, 52, 40);
	mTexture->Parent(this);
	mTexture->Position(Vect2_Zero);

	mSpeed = 100.0f;
}

Enemy::~Enemy() {

	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;

}

Enemy::State Enemy::CurrentState() {
	return mCurrentState;
}


void Enemy::Update() {

	if (Active()) {
		HandleStates();
	}

}

void Enemy::Render() {

	if (Active()) {
		RenderStates();
	}

}



void Enemy::HandleFlyInState() {

	if (mCurrentWaypoint < sPaths[mCurrentPath].size()) {
		Vector2 dist = sPaths[mCurrentPath][mCurrentWaypoint] - Position();
		Translate(dist.Normalized()*mSpeed*mTimer->DeltaTime(), WORLD);
		Rotate(atan2(dist.y, dist.x)*RAD_TO_DEG + 90.0f);

		if ((sPaths[mCurrentPath][mCurrentWaypoint] - Position()).MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			//we have made it to the next waypoint
			mCurrentWaypoint++;
		}
		
	}else {
		mCurrentState = InFormation;
	}

}

void Enemy::HandleInFormationState() {}

void Enemy::HandleDiveState() {}

void Enemy::HandleDeadState() {}

void Enemy::HandleStates() {

	switch (mCurrentState) {
	case FlyIn:
		HandleFlyInState();
		break;
	case Diving:
		HandleDiveState();
		break;
	case InFormation:
		HandleInFormationState();
		break;
	case Dead:
		HandleDeadState();
		break;
	}

}

void Enemy::RenderInFormationState() {
	
	mTexture->Render();

	//todo remove this
	for (int i = 0; i < sPaths[mCurrentPath].size() - 1; i++) {
		Graphics::Instance()->DrawLine(sPaths[mCurrentPath][i].x,
			sPaths[mCurrentPath][i].y,
			sPaths[mCurrentPath][i + 1].x,
			sPaths[mCurrentPath][i + 1].y
		);
	}

}

void Enemy::RenderFlyInState() {

	mTexture->Render();

	for (int i = 0; i < sPaths[mCurrentPath].size() - 1; i++) {
		Graphics::Instance()->DrawLine(sPaths[mCurrentPath][i].x,
			sPaths[mCurrentPath][i].y,
			sPaths[mCurrentPath][i + 1].x,
			sPaths[mCurrentPath][i + 1].y
		);
	}

}

void Enemy::RenderDiveState() {}

void Enemy::RenderDeadState() {}


void Enemy::RenderStates() {

	switch (mCurrentState) {
	case FlyIn:
		RenderFlyInState();
		break;
	case Diving:
		RenderDiveState();
		break;
	case InFormation:
		RenderInFormationState();
		break;
	case Dead:
		RenderDeadState();
		break;
	}

}