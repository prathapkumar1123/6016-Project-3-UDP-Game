#include "SceneLevel1.h"

#include "../Physics/PhysicsEngine.h"



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

	PhysicsEngine::getInstance().setObjects(&mObjectsToDraw);
}

void SceneLevel1::updateScene(float deltaTime) {
	if (getLightMananger() != nullptr)
		getLightMananger()->UpdateUniformValues(getShaderProgramId());

	//networkManager.SendPlayerPositionToServer(player->drawPosition.x, player->drawPosition.z);
	//networkManager.Update();
}

void SceneLevel1::processKeyboardInput(float deltaTime) {
	Camera::getInstance().processKeyboardInput(deltaTime);

	if (player != nullptr) {
		player->processKeyboardInput(getWindow(), deltaTime);
	}
}

void SceneLevel1::addPlayers() {
	
}