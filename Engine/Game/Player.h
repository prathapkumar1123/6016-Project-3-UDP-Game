#pragma once

#include "../Graphics/GameObject/GameObject.h"
#include "../Core/OpenGlCommons.h"
#include "../GameEngine/Camera.h"

class Player: public GameObject  {
public:
	Player();
	~Player();

	virtual void update(float deltaTime) override;
	virtual void resolveCollisions() override;

	Direction direction;

	void setPlayerToIdle();
	void setPlayerToWalking(Direction direction);
	void setPlayerToDeath();

	void shoot(float deltaTime);
	void movePlayer(glm::vec3 velocity, Direction direction);

	void updateCameraPosition();

	void processKeyboardInput(GLFWwindow* window, float deltaTime);

	std::vector<GameObject*>* mObjectsToDraw;

	bool isPlayerAlive;

private:

	glm::vec3 lastPosition;
	float lastUpdatedTime;
	float lastShootedTime;
	float lastHitTime;

	bool isPlayerIdle;
	bool isShooting;

	int health = DEFAULT_PLAYER_HEALTH;

	float shootDelay = 0.2f;
};

