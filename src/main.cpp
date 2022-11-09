#include "libs.hpp"
#include "class/Game.hpp"

int main()
{
    Game engine;
    Game::instance = &engine;

    while (engine.isRunning()) {
        engine.update();
        engine.render();
    }
}
