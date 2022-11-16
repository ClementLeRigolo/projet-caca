#include "libs.hpp"
#include "class/Game.hpp"

int main()
{
    Game& engine = Game::getInstance();

    while (engine.isRunning()) {
        engine.update();
        engine.render();
    }
}
