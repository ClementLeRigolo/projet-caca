#include "class/Game.hpp"
#include "class/system/Timer.hpp"

void doNothingFunc() {};

void exempleFunc()
{
    Level* level = (Level*)Game::getInstance().getCurrentScene();

    level->addEntity(Vector2f(randomNumber(0, 1920), randomNumber(0, 1920)));
    cout << Timer::getSeconds() << endl;
}

void buttonExitGameFunc()
{
    Game::getInstance().getRender()->getWindow().close();
}

void buttonBackMainMenuFunc()
{
    Game::getInstance().setCurrentScene(&Game::getInstance().getScene(MAIN_MENU));
}

void buttonGoToSettingsFunc()
{
    Game::getInstance().setCurrentScene(&Game::getInstance().getScene(SETTINGS_MENU));
}

void buttonPlayGameFunc()
{
    Game::getInstance().setCurrentScene(&Game::getInstance().getScene(LEVEL_1));
}

void toggleVsyncFunc(bool toggle)
{
    Game::getInstance().getRender()->setVsyncEnabled(toggle);
}
