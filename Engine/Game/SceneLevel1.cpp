#include "SceneLevel1.h"

#include "../Physics/PhysicsEngine.h"
#include "../Core/RandomGenerator.h"

#include "../player_state.pb.h"

SceneLevel1::SceneLevel1(int shaderProgramId, std::string sceneFile): BaseScene(shaderProgramId, sceneFile) {
	initialize();
}

SceneLevel1::~SceneLevel1() {

}

void SceneLevel1::onInit() {

}

void SceneLevel1::onSceneLoaded() {
	BaseScene::onSceneLoaded();


	for (GameObject* obj : mObjectsToDraw) {

		if (obj->simpleName == "floor") {
			glm::vec3 minB = obj->getBoundingBoxMin();
			glm::vec3 maxB = obj->getBoundingBoxMax();

			minB.y -= 100.0f;
			maxB.y += 100.0f;

			minB.x += 10.0f;
			maxB.x -= 10.0f;

			minB.z += 10.0f;
			maxB.z -= 10.0f;

			PhysicsEngine::getInstance().setSceneBounds(minB, maxB);
		}
	}

	addPlayers();

	PhysicsEngine::getInstance().setObjects(&mObjectsToDraw);
}

void SceneLevel1::updateScene(float deltaTime) {
	if (getLightMananger() != nullptr)
		getLightMananger()->UpdateUniformValues(getShaderProgramId());

	networkManager->Update();

	Camera::getInstance().updateViewMatrix();

	if (currentPlayersAdded != networkManager->scene.players_size()) {
		addPlayers();
	}

	currentPlayersAdded = networkManager->scene.players_size();



	/*for (int i = 0; i < networkManager->m_NetworkedPositions.size(); i++) {
		glm::vec3 position(networkManager->m_NetworkedPositions[i].x, 0.f, networkManager->m_NetworkedPositions[i].z);
		mNetworkPlayers[i]->bIsVisible = true;
		mNetworkPlayers[i]->playerId = networkManager->m_NetworkedPositions[i].id;
		mNetworkPlayers[i]->drawPosition += position;
	}

	if (networkManager->isNewPlayerAdded) {

	}*/

}

void SceneLevel1::processKeyboardInput(float deltaTime) {
	//Camera::getInstance().processKeyboardInput(deltaTime);

	if (player != nullptr) {
		player->processKeyboardInput(getWindow(), deltaTime);
	}

	glm::vec3 position = glm::vec3(0.f);
	float speed = 10.0f;

	if (glfwGetKey(getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		position += glm::vec3(0.0f, 0.0f, -0.1f);
	}

	if (glfwGetKey(getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		position += glm::vec3(0.0f, 0.0f, 0.1f);
	}
	if (glfwGetKey(getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		position += glm::vec3(-0.1f, 0.0f, 0.0f);
	}
	if (glfwGetKey(getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		position += glm::vec3(0.1f, 0.0f, 0.0f);
	}
	
	networkManager->SendPlayerPositionToServer(position.x * speed, position.z * speed);

}

void SceneLevel1::addPlayers() {

	for (int i = 0; i < networkManager->scene.players_size(); i++) {
		game::Player gamePlayer = networkManager->scene.players().Get(i);

		bool playerExists = false;
		for (const auto& existingPlayer : mNetworkPlayers) {
			if (existingPlayer->playerId == gamePlayer.id()) {
				playerExists = true;
				break;
			}
		}

		// If player doesn't exist, add a new player
		if (!playerExists) {
			Player* player = new Player();
			player->playerId = gamePlayer.id();
			player->drawPosition = glm::vec3(gamePlayer.position().x() + i * 100, 0.f, gamePlayer.position().z() + i * 100);
			player->bIsVisible = gamePlayer.isalive();
			player->wholeObjectDebugColourRGBA = playerColors[i];

			mObjectsToDraw.push_back(player);
			mNetworkPlayers.push_back(player);
		}
	}
}