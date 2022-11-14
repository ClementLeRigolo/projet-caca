#include "libs.hpp"
#include "class/Game.hpp"
#include "class/Inventory.hpp"
#include "class/Logger.hpp"
#include "class/Collection.hpp"

int main()
{
    Game& engine = Game::getInstance();

    while (engine.isRunning()) {
        engine.update();
        engine.render();
    }
}
