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
    Game::getInstance().setCurrentScene(&Game::getInstance().getScene(MAIN_MENU), true);
}

void buttonGoToSettingsFunc()
{
    Game::getInstance().setCurrentScene(&Game::getInstance().getScene(SETTINGS_MENU), false);
}

void buttonGoToLevelEditor()
{
    Game::getInstance().setCurrentScene(&Game::getInstance().getScene(LEVEL_EDITOR), false);
}

void buttonPlayGameFunc()
{
    Game::getInstance().setCurrentScene(&Game::getInstance().getScene(LEVEL_1), true);
}

void toggleVsyncFunc(bool toggle)
{
    Game::getInstance().getRender()->setVsyncEnabled(toggle);
}

void buttonLevelEditorMoveMode()
{
    LevelEditor* level = (LevelEditor*)Game::getInstance().getCurrentScene();

    level->setEditMode(EditMode::MOVE);
}

void buttonLevelEditorSelectMode()
{
    LevelEditor* level = (LevelEditor*)Game::getInstance().getCurrentScene();

    level->setEditMode(EditMode::SELECT);
}

void buttonLevelEditorResizeMode()
{
    LevelEditor* level = (LevelEditor*)Game::getInstance().getCurrentScene();

    level->setEditMode(EditMode::RESIZE);
}

void buttonLevelEditorPlaceMode()
{
    LevelEditor* level = (LevelEditor*)Game::getInstance().getCurrentScene();

    level->setEditMode(EditMode::PLACE);
}

void buttonShowLevelEditorSave()
{
    LevelEditor* level = (LevelEditor*)Game::getInstance().getCurrentScene();

    level->toggleSavePopup(true);
}

void buttonHideLevelEditorSave()
{
    LevelEditor* level = (LevelEditor*)Game::getInstance().getCurrentScene();

    level->toggleSavePopup(false);
}

void buttonApplyLevelEditorSave()
{
    LevelEditor* level = (LevelEditor*)Game::getInstance().getCurrentScene();

    level->setSaving(true);
    level->toggleSavePopup(false);
}

void buttonCloseLevelEditorSave()
{
    LevelEditor* level = (LevelEditor*)Game::getInstance().getCurrentScene();

    level->toggleSavePopup(false);
}