#include "class/Item.hpp"

Item::Item(int id, string name, string description, Texture texture)
{
    id = m_id;
    name = m_name;
    description = m_description;
    texture = m_texture;
}

int Item::getId() const { return m_id; }

void Item::setId(int id) { m_id = id; }

string Item::getName() const { return m_name; }

void Item::setName(string name) { m_name = name; }

string Item::getDescription() const { return m_description; }

void Item::setDescription(string description) { m_description = description; }

Texture* Item::getTexture() { return &m_texture; }

void Item::setTexture(Texture texture) { m_texture = texture; }
