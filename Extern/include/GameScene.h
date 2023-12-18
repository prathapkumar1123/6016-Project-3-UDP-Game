#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct vec2 {
    float x;
    float z;
};

struct UserInput {
    int32_t id;
    int32_t input;
};

struct Player {
    int32_t id;
    bool isAlive;
    bool isShot;
    vec2 position;
    int32_t state;
};

enum BulletState {
    ACTIVE = 0,
    IN_ACTIVE = 1
};

struct Bullet {
    BulletState state;
    vec2 position;
    vec2 velocity;
};

struct GameScene {
    int32_t id;
    std::vector<Player> players;
    std::vector<Bullet> bullets;
};