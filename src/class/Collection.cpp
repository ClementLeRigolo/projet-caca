#include "class/Collection.hpp"
#include "class/Asset.hpp"

void Collection::loadCollection()
{
    LEVEL_1.getView()->setCenter(960 / 2, 540 / 2);
    LEVEL_1.getView()->setSize(960, 540);
}

// scenes
Scene Collection::INTRO_CREDITS = Scene();
Scene Collection::START_MENU = Scene();
Scene Collection::LEVEL_1 = Scene();
