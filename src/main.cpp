#include "libs.hpp"
#include "class/Game.hpp"
#include "class/AssetManager.hpp"

int main()
{
    Music music;
    music.openFromFile(AUDIO_PATH + "music/music.ogg");

    AssetManager& assetManager = AssetManager::getInstance();

    Game& engine = Game::getInstance();

    engine.setMusic(&music);
    engine.Initialize();
    while (engine.isRunning()) {
        engine.update();
        engine.render();
    }
}
