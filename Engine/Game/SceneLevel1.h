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

    std::vector<GameObject*> mNetworkPlayers;

private:

    int shaderProgramId;

    std::string sceneFile;
    Player* player;

};