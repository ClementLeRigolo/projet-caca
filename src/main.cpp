#include "libs.hpp"
#include "class/Game.hpp"

int main()
{
    Game engine = Game();

    while (engine.isRunning()) {
        engine.update();
        engine.getRender()->update();
    }
}
