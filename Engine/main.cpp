#include "GameEngine/GameEngine.h"
#include "Game/SceneLevel1.h"

#include <iostream>


int main() {
	std::cout << "Please wait, Starting the scene..." << std::endl;

    GameEngine engine = GameEngine();
    SceneLevel1 scene(engine.getShaderProgramId(), "scene_1.json");

    engine.setCurrentScene(&scene);
    engine.init();
    engine.runGameLoop();
    engine.stop();

    return 0;
}