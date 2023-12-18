#pragma once

#include "../GameEngine/BaseScene.h"
#include "../Game/Player.h"

#include <vector>

class SceneLevel1 : public BaseScene {

public:
    SceneLevel1(int shaderProgramId, std::string sceneFile);
    ~SceneLevel1();

    void onInit() override;
    void onSceneLoaded() override;
    void updateScene(float deltaTime) override;
    void processKeyboardInput(float deltaTime) override;

    void addPlayers();

    std::vector<Player*> mNetworkPlayers;

private:

    int shaderProgramId;

    std::string sceneFile;
    Player* player;

    int currentPlayersAdded = 0;

    std::vector<glm::vec4> playerColors = {
        glm::vec4(1.f, 0.f, 0.f, 1.0f),
        glm::vec4(0.f, 1.f, 0.f, 1.0f),
        glm::vec4(0.f, 0.f, 1.f, 1.0f),
        glm::vec4(1.f, 0.f, 1.f, 1.0f),
    };

};