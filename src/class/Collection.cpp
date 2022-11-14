#include "class/Collection.hpp"
#include "class/Asset.hpp"

void Collection::loadCollection()
{
}

// scenes
Scene Collection::INTRO_CREDITS = Scene();
MainMenu Collection::MAIN_MENU = MainMenu();
SettingsMenu Collection::SETTINGS_MENU = SettingsMenu();
Level Collection::LEVEL_1 = Level();

// items
Item Collection::TEST_ITEM = Item(0, "Test item", "this is a dev test item", Texture(), false);
