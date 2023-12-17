#pragma once

#include <iostream>
#include <random>
#include <string>
#include <vector>

enum Direction {
	LEFT, RIGHT, FORWARD, BACKWARD, LF, RF, LB, RB
};

enum SHOT_BY {
	PLAYER, ENEMY
};

enum BULLET_TYPE {
	BULLET, MISSILE
};

enum ENEMY_TYPE {
	BRAIN, GRUNT, HULK, SPHEREOID, ENFORCER, TANK
};

const int DEFAULT_PLAYER_HEALTH = 100;
const int ENEMY_COLLIDE_DAMAGE = 30;

const float BULLET_SPEED = 2.0f;
const float ENEMY_MOVEMENT_SPEED = 20.0f;
const float PLAYER_MOVEMENT_SPEED = 3.0f;

const float ENEMY_CHANGE_DIRECTION_DELAY = 3.0f;

const float HUMAN_MOVEMENT_SPEED = 12.0f;

const float SPHEREIOD_CREATION_TIME = 15.0f;

const float SPHEREIOD_ANIMATE_DELAY = 0.1f;

const float ENFORCER_ANIMATE_DELAY = 0.5f;

const float SPHEREIOD_MOVEMENT_SPEED = 30.0f;

const float HULK_MOVEMENT_SPEED = 10.0f;

const float EXPLODE_DELAY_TRANISITION_TIME = 0.2f;

const float ENFORCER_SHOOT_DELAY_TIME = 5.0f;

const int DAMAGE_BY_BULLET = 30;

const float HUMAN_TRACKING_RADIUS = 150.0f;

const float BULLET_ANIMATE_DELAY = 0.1f;


// Player
const std::string PLAYER_LEFT_1 = "player1.ply";
const std::string PLAYER_LEFT_2 = "player2.ply";
const std::string PLAYER_LEFT_3 = "player3.ply";

const std::string PLAYER_RIGHT_1 = "player4.ply";
const std::string PLAYER_RIGHT_2 = "player5.ply";
const std::string PLAYER_RIGHT_3 = "player6.ply";

const std::string PLAYER_BACK_1 = "player7.ply"; // IDLE
const std::string PLAYER_BACK_2 = "player8.ply";
const std::string PLAYER_BACK_3 = "player9.ply";

const std::string PLAYER_FRONT_1 = "player10.ply";
const std::string PLAYER_FRONT_2 = "player11.ply";
const std::string PLAYER_FRONT_3 = "player12.ply";

// Other
const std::string HUMAN_DEATH = "humandeath.ply";