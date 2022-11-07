#include "libs.hpp"
#include "class/Game.hpp"
#include "class/Collection.hpp"

int main()
{
    Game engine = Game();
    float fps = 0;

    while (engine.isRunning()) {
        engine.update();
        engine.getRender()->update();
    }
    engine.getRender()->~Render();
}
