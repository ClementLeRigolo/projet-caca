#include "libs.hpp"
#include "class/Game.hpp"

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

sf::Vector2i getMousePosition(RenderWindow* window)
{
    sf::Vector2i mouse_pos0 = Mouse::getPosition(*window);
    sf::Vector2f mouse_pos;

    mouse_pos = window->mapPixelToCoords(mouse_pos0, window->getView());
    return sf::Vector2i(mouse_pos);
}

bool DoMouseIntersect(Vector2i mousePos, FloatRect to_check)
{
    int posX_offset = to_check.left + to_check.width;
    int posY_offset = to_check.top + to_check.height;
    sf::Vector2i pos = sf::Vector2i(to_check.left, to_check.top);
    sf::Vector2i pos_offset = {posX_offset, posY_offset};

    if ((mousePos.x >= pos.x && mousePos.x <= pos_offset.x)
        && (mousePos.y >= pos.y && mousePos.y <= pos_offset.y))
        return true;
    else
        return false;
}

int randomNumber(int min_num, int max_num)
{
    int result = 0;
    int low_num = 0;
    int hi_num = 0;

    if (min_num < max_num) {
        low_num = min_num;
        hi_num = max_num + 1;
    } else {
        low_num = max_num + 1;
        hi_num = min_num;
    }
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}