#pragma once
#include "BezierPath.h"
#include "AnimatedTexture.h"
#include "PhysEntity.h"
#include "Player.h"
#include "Formation.h"

using namespace SDLFramework;

class Enemy : public PhysEntity {

public:

	enum State {FlyIn, InFormation, Diving, Dead};
	enum EnemyType {Butterfly, Wasp, Boss};

	static void CreatePaths();
	static void SetFormation(Formation* formation);

	State CurrentState();
	EnemyType Type();
	int Index();

	Enemy(int path, int index, bool challenge);
	virtual ~Enemy();

	virtual void Dive(int type = 0);

	void Update() override;
	void Render() override;

	


protected:

	static Formation* sFormation;
	static std::vector< std::vector<Vector2>> sPaths;
	static Player* sPlayer;

	Timer* mTimer;

	Texture* mTexture;

	State mCurrentState;
	EnemyType mType;

	int mIndex;//formation

	bool mChallengeStage;

	Vector2 mDiveStartPosition;

	unsigned int mCurrentPath;
	unsigned int mCurrentWaypoint;

	float mSpeed;

	const float EPSILON = 50.0f;

	virtual void PathComplete();
	virtual void FlyInComplete();

	void JoinFormation();

	virtual Vector2 WorldFormationPosition();
	virtual Vector2 LocalFormationPosition() = 0;

	virtual void HandleFlyInState();
	virtual void HandleInFormationState();
	virtual void HandleDiveState() = 0;
	virtual void HandleDeadState() = 0;

	void HandleStates();

	virtual void RenderFlyInState();
	virtual void RenderInFormationState();
	virtual void RenderDiveState() = 0;
	virtual void RenderDeadState() = 0;

	void RenderStates();

};