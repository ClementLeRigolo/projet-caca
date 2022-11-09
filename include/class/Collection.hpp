#pragma once

#include "class/Scene.hpp"
#include "class/Item.hpp"
#include "class/Entity.hpp"

class Collection
{
    public:
        static void loadCollection();

        // scenes
        static Scene INTRO_CREDITS;
        static Menu MAIN_MENU;
        static Level LEVEL_1;

        //items
        static Item TEST_ITEM;
        
        // entities
        static Entity TEST_ENTITY;
};