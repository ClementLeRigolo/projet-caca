#include "libs.hpp"

sf::Vector2f getCenter(sf::Texture texture)
{
    sf::Vector2u center = texture.getSize();

    center.x /= 2;
    center.y /= 2;
    return sf::Vector2f(center.x, center.y);
}

sf::Vector2f getCenter(float width, float height)
{
    return sf::Vector2f(width / 2.0, height / 2.0);
}

sf::Vector2f getCenter(sf::Shape &shape)
{
    return sf::Vector2f(shape.getGlobalBounds().width / 2.0, shape.getGlobalBounds().height / 2.0);
}
