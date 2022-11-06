#include "libs.hpp"
#include "class/Game.hpp"
#include "class/Collection.hpp"

int main()
{
    Game engine = Game();

    while (engine.isRunning()) {
        engine.update();
        engine.getRender()->update();
    }
    engine.getRender()->~Render();
}
