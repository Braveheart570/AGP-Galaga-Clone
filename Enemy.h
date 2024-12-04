#pragma once
#include "BezierPath.h"
#include "AnimatedTexture.h"
#include "PhysEntity.h"
#include "Player.h"

using namespace SDLFramework;

class Enemy : public PhysEntity {

public:

	enum State {FlyIn, InFormation, Diving, Dead};

	static void CreatePaths();

	State CurrentState();

	Enemy(int path);
	virtual ~Enemy();

	void Update() override;
	void Render() override;


protected:

	static std::vector< std::vector<Vector2>> sPaths;
	static Player* sPlayer;

	Timer* mTimer;

	Texture* mTexture;

	State mCurrentState;

	unsigned int mCurrentPath;
	unsigned int mCurrentWaypoint;

	float mSpeed;

	const float EPSILON = 50.0f;

	virtual void HandleFlyInState();
	virtual void HandleInFormationState();
	virtual void HandleDiveState();
	virtual void HandleDeadState();

	void HandleStates();

	virtual void RenderFlyInState();
	virtual void RenderInFormationState();
	virtual void RenderDiveState();
	virtual void RenderDeadState();

	void RenderStates();

};