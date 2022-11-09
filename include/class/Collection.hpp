#pragma once

#include "class/Scene.hpp"
#include "class/Weapon.hpp"
#include "class/Entity.hpp"

class Collection
{
    public:
        static void loadCollection();

        // scenes
        static Scene INTRO_CREDITS;
        static Scene START_MENU;
        static Scene LEVEL_1;

        //items
        static Item TEST_ITEM;
        
        // entities
        static Entity TEST_ENTITY;
};