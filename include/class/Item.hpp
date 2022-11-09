#pragma once

#include "libs.hpp"

class Item
{
    protected:
        int m_id;
        string m_name;
        string m_description;
        Texture m_texture;
        bool m_equipable;
        
    public:
        Item();
        Item(int id, string name, string description, Texture texture, bool equipable);
        int getId() const;
        void setId(int id);
        string getName() const;
        void setName(string name);
        string getDescription() const;
        void setDescription(string description);
        Texture* getTexture();
        void setTexture(Texture texture);
        bool isEquipable() const;
        void setEquipable(bool equipable);
};
