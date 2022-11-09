#include "class/Collection.hpp"
#include "class/Asset.hpp"

void Collection::loadCollection()
{
}

// scenes
Scene Collection::INTRO_CREDITS = Scene();
Menu Collection::MAIN_MENU = Menu();
Level Collection::LEVEL_1 = Level();

// items
Item Collection::TEST_ITEM = Item(0, "Test item", "this is a dev test item", Texture(), false);
