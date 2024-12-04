#include "Bullet.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Bullet::Bullet(bool friendly) {

	mTimer = Timer::Instance();
	mTexture = new Texture("Bullet.png");
	mTexture->Parent(this);
	mTexture->Position(Vect2_Zero);
	mSpeed = 500.0f;

	Reload();

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
	if (friendly) {
		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::FriendlyProjectile);
	}
	else {
		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::HostileProjectile);
	}
	

}

Bullet::~Bullet() {

	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;

}

bool Bullet::IgnoreCollisions() {
	return !Active();
}

void Bullet::Fire(Vector2 pos) {
	Position(pos);
	Active(true);
}

void Bullet::Reload() {
	Active(false);
}

void Bullet::Hit(PhysEntity* other) {

	Reload();

}

void Bullet::Update() {
	if (Active()) {
		Translate(-Vect2_Up * mSpeed * mTimer->DeltaTime());

		Vector2 pos = Position();
		if (pos.y < -OFFSCREEN_BUFFER) {
			Reload();
		}

	}
}

void Bullet::Render() {
	if (Active()) {
		mTexture->Render();
		PhysEntity::Render();
	}
}