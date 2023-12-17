#include "Bullet.h"

class Bullet::BulletImpl {

public:
	glm::vec3 initialPosition;
	int shotByPlayerId;
};


Bullet::Bullet(glm::vec3 velocity, glm::vec3 initialPosition): GameObject("bullet.ply") {
	this->velocity = velocity;
	this->inverse_mass = 1.0f;
	this->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	this->drawScale = glm::vec3(0.2, 0.2, 0.2);
	this->drawPosition = initialPosition;
	this->isRigidBody = true;
	this->bDoNotLight = true;
	this->shapeType = AABB;
	this->boundsOffset = 0.2f;
	this->shapeType = AABB;
	this->pShape = new sPhysicsProperties::sAABB(this->getBoundingBoxMin(), this->getBoundingBoxMax());

	impl = new BulletImpl();
}

Bullet::~Bullet() {

}

void Bullet::setShotBy(int shotByPlayerId) {
	impl->shotByPlayerId = shotByPlayerId;
}

void Bullet::update(float deltaTime) {

	if (isGoingOutOfBounds) {
		this->isOutOfBounds = true;
		this->isDestroyed = true;
	}

	this->drawPosition += this->velocity * BULLET_SPEED;

}

void Bullet::resolveCollisions() {
	/*if (impl->shotByPlayerId != shotByPlayerId) {
		if (collisionWith["enemy"] != nullptr ||
			collisionWith["grunt"] != nullptr ||
			collisionWith["hulk"] != nullptr ||
			collisionWith["sphereoid"] != nullptr ||
			collisionWith["enforcer"] != nullptr) {

			collisionWith["enemy"] = nullptr;
			collisionWith["grunt"] = nullptr;
			collisionWith["enforcer"] = nullptr;
			collisionWith["hulk"] = nullptr;
			collisionWith["sphereoid"] = nullptr;

			this->isOutOfBounds = true;
		}
	}*/
}