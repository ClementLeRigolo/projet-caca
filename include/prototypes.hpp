#pragma once

void buildLevel1();

// Utility functions
sf::Vector2f getCenter(sf::Texture texture);
sf::Vector2f getCenter(float width, float height);
sf::Vector2f getCenter(sf::Shape &shape);