#include "Player.h"
#include "Bullet.h"

#include "../Core/RandomGenerator.h"


#include <iostream>

Player::Player(): GameObject(PLAYER_BACK_1) {
	this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->inverse_mass = 0.0f;
	this->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	this->isRigidBody = true;
	this->isPlayerAlive = true;
	this->bUseDebugColours = true;
	this->bDoNotLight = true;
	this->setUniformDrawScale(0.3f);

	this->wholeObjectDebugColourRGBA = glm::vec4(genRandom(0.f, 1.f), genRandom(0.f, 1.f), genRandom(0.f, 1.f), 1.f);

	this->shapeType = AABB;
	this->pShape = new sPhysicsProperties::sAABB(this->getBoundingBoxMin(), this->getBoundingBoxMax());
}

Player::~Player() {

}

void Player::update(float deltaTime) {
	if ((deltaTime - this->lastUpdatedTime) > 0.3f && this->velocity == glm::vec3(0.0f) && isPlayerAlive) {
		setPlayerToIdle();
	}

	if (!isPlayerAlive) {
		setPlayerToDeath();
	}
	
	//this->velocity += this->acceleration * deltaTime;
	//this->drawPosition += this->velocity * deltaTime;

	//updateCameraPosition();
}

void Player::movePlayer(glm::vec3 velocity, Direction direction) {
	this->direction = direction;
	if (velocity != glm::vec3(0.0f)) {
		this->drawPosition += velocity * PLAYER_MOVEMENT_SPEED;
		setPlayerToWalking(direction);
	}
	else {
		setPlayerToIdle();
	}
}

void Player::updateCameraPosition() {
	Camera::getInstance().position.x = this->drawPosition.x;
	Camera::getInstance().position.z = this->drawPosition.z + 520.0f;
}

void Player::shoot(float deltaTime) {
	lastShootedTime = deltaTime;
	isShooting = true;
	glm::vec3 bulletVelocity(0.0f);
	switch (direction) {
	case LEFT:
		bulletVelocity.x = -1.0f; // Move along the negative X axis
		break;
	case RIGHT:
		bulletVelocity.x = 1.0f;  // Move along the positive X axis
		break;
	case FORWARD:
		bulletVelocity.z = -1.0f; // Move along the negative Z axis
		break;
	case BACKWARD:
		bulletVelocity.z = 1.0f;  // Move along the positive Z axis
		break;
	case LF:
		bulletVelocity.x = -1.0f; // Move along the negative X axis
		bulletVelocity.z = -1.0f; // Move along the negative Z axis (Left Forward)
		break;
	case RF:
		bulletVelocity.x = 1.0f;  // Move along the positive X axis
		bulletVelocity.z = -1.0f; // Move along the negative Z axis (Right Forward)
		break;
	case LB:
		bulletVelocity.x = -1.0f; // Move along the negative X axis
		bulletVelocity.z = 1.0f;  // Move along the positive Z axis (Left Backward)
		break;
	case RB:
		bulletVelocity.x = 1.0f;  // Move along the positive X axis
		bulletVelocity.z = 1.0f;  // Move along the positive Z axis (Right Backward)
		break;
	default:
		break;
	}

	glm::vec3 bulletPos(this->drawPosition);
	bulletPos.y = 0.0f;

	bulletVelocity = glm::normalize(bulletVelocity);

	Bullet* bullet = BulletBuilder(bulletPos)
		.setVelocity(bulletVelocity)
		.setShotBy(PLAYER)
		.build();

	mObjectsToDraw->push_back(bullet);
	isShooting = false;
}

void Player::resolveCollisions() {
	if (collisionWith["bullet"] != nullptr ) {
		setPlayerToDeath();
	}
}

void Player::processKeyboardInput(GLFWwindow* window, float deltaTime) {
	glm::vec3 moveDirection(0.0f);
	Direction direction = this->direction;
	glm::vec3 rotation = glm::vec3(0.0f);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (!isShooting && deltaTime - lastShootedTime > shootDelay && isPlayerAlive) {
			shoot(deltaTime);
		}	
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		moveDirection = glm::vec3(0.0f, 0.0f, -0.1f);
		direction = Direction::FORWARD;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		moveDirection = glm::vec3(0.0f, 0.0f, 0.1f);
		direction = Direction::BACKWARD;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		moveDirection = glm::vec3(-0.1f, 0.0f, 0.0f);
		direction = Direction::LEFT;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		moveDirection = glm::vec3(0.1f, 0.0f, 0.0f);
		direction = Direction::RIGHT;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		moveDirection = glm::vec3(0.1f, 0.0f, -0.1f);
		direction = Direction::RF;
		rotation.y = 45.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		moveDirection = glm::vec3(-0.1f, 0.0f, -0.1f);
		direction = Direction::LF;
		rotation.y = -45.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		moveDirection = glm::vec3(0.1f, 0.0f, 0.1f);
		direction = Direction::RB;
		rotation.y = -45.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		moveDirection = glm::vec3(-0.1f, 0.0f, 0.1f);
		direction = Direction::LB;
		rotation.y = 45.0f;
	}

	if (moveDirection != glm::vec3(0.0f) && isPlayerAlive) {
		this->setRotationFromEuler(glm::radians(rotation));
		this->movePlayer(moveDirection, direction);
		this->lastUpdatedTime = deltaTime;
	}
}

void Player::setPlayerToIdle() {
	isPlayerIdle = true;
}

void Player::setPlayerToDeath() {
	isPlayerAlive = false;
	this->setFileName(HUMAN_DEATH);
}

void Player::setPlayerToWalking(Direction direction) {
	isPlayerIdle = false;
	if (glm::distance(this->lastPosition, this->drawPosition) > 1.0f) {
		switch (direction)
		{
		case LEFT:
		case LF:
		case LB:
			if (this->getFileName() == PLAYER_LEFT_1)
				this->setFileName(PLAYER_LEFT_2);
			else if (this->getFileName() == PLAYER_LEFT_2)
				this->setFileName(PLAYER_LEFT_3);
			else
				this->setFileName(PLAYER_LEFT_1);
			break;
		case RIGHT:
		case RF:
		case RB:
			if (this->getFileName() == PLAYER_RIGHT_1)
				this->setFileName(PLAYER_RIGHT_2);
			else if (this->getFileName() == PLAYER_RIGHT_2)
				this->setFileName(PLAYER_RIGHT_3);
			else
				this->setFileName(PLAYER_RIGHT_1);
			break;
		case FORWARD:
			if (this->getFileName() == PLAYER_FRONT_1)
				this->setFileName(PLAYER_FRONT_2);
			else if (this->getFileName() == PLAYER_FRONT_2)
				this->setFileName(PLAYER_FRONT_3);
			else
				this->setFileName(PLAYER_FRONT_1);
			break;
		case BACKWARD:
			if (this->getFileName() == PLAYER_BACK_1)
				this->setFileName(PLAYER_BACK_2);
			else if (this->getFileName() == PLAYER_BACK_2)
				this->setFileName(PLAYER_BACK_3);
			else
				this->setFileName(PLAYER_BACK_1);
			break;
		default:
			break;
		}

		this->lastPosition = drawPosition;
	}
}