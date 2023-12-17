#pragma once

#include "../Graphics/GameObject/GameObject.h"

class Bullet: public GameObject
{
public:
	Bullet(glm::vec3 velocity, glm::vec3 initialPosition);
	~Bullet();

	virtual void resolveCollisions() override;
	virtual void update(float deltaTime) override;

    void setShotBy(int shotByPlayerId);

private:
    class BulletImpl;
    BulletImpl* impl;
};

class BulletBuilder {
public:
    BulletBuilder(glm::vec3 initialPosition) : initialPosition(initialPosition) {}


    BulletBuilder& setVelocity(glm::vec3 velocity) {
        this->velocity = velocity;
        return *this;
    }

    BulletBuilder& setShotBy(int shotByPlayerId) {
        this->shotByPlayerId = shotByPlayerId;
        return *this;
    }

    Bullet* build() {
        Bullet* bullet = new Bullet(velocity, initialPosition);
        bullet->setShotBy(shotByPlayerId);
        bullet->simpleName = "bullet_" + std::to_string(shotByPlayerId);
        bullet->velocity = velocity;

        return bullet;
    }

private:
    std::string name;
    glm::vec3 velocity;
    glm::vec3 initialPosition;

    int shotByPlayerId;
};

