#pragma once

#include "libs.hpp"

class Item
{
    private:
        int m_id;
        string m_name;
        string m_description;
        Texture m_texture;
        
    public:
        Item(int id, string name, string description, Texture texture);
        int getId() const;
        void setId(int id);
        string getName() const;
        void setName(string name);
        string getDescription() const;
        void setDescription(string description);
        Texture* getTexture();
        void setTexture(Texture texture);
};
