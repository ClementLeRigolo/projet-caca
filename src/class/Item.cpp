#include "class/Item.hpp"

Item::Item() {}

Item::Item(int id, string name, string description, Texture texture, bool equipable) :
    m_id(id), m_name(name), m_description(description), m_texture(texture), m_equipable(equipable) {}

int Item::getId() const { return m_id; }

void Item::setId(int id) { m_id = id; }

string Item::getName() const { return m_name; }

void Item::setName(string name) { m_name = name; }

string Item::getDescription() const { return m_description; }

void Item::setDescription(string description) { m_description = description; }

Texture* Item::getTexture() { return &m_texture; }

void Item::setTexture(Texture texture) { m_texture = texture; }

bool Item::isEquipable() const { return m_equipable; }

void Item::setEquipable(bool equipable) { m_equipable = equipable; }
