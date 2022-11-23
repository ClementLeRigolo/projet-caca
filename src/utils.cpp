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

sf::Vector2f getCenter(sf::Text &shape)
{
    return sf::Vector2f(shape.getGlobalBounds().width / 2.0, shape.getGlobalBounds().height / 2.0);
}

sf::Vector2i getMousePosition(RenderWindow& window)
{
    sf::Vector2i mouse_pos0 = Mouse::getPosition(window);
    sf::Vector2f mouse_pos;

    mouse_pos = window.mapPixelToCoords(mouse_pos0, window.getView());
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

float damp(float source, float smoothing, float dt)
{
    return source * pow(smoothing, dt);
}

double lerp(double a, double b, double t)
{
    if (t <= 0.5)
        return a+(b-a)*t;
    else
        return b-(b-a)*(1.0-t);
}

double clamp(double min, double max, double value)
{
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}

sf::Color smoothColor(sf::Color c1, sf::Color c2, double prog)
{
    float diff_r = c1.r - c2.r;
    float diff_g = c1.g - c2.g;
    float diff_b = c1.b - c2.b;
    float diff_a = c1.a - c2.a;
    sf::Color res = sf::Color(0, 0, 0, 0);

    if (prog > 1)
        prog = 1;
    if (prog < 0)
        prog = 0;
    res.r = c1.r + (diff_r * prog);
    res.g = c1.g + (diff_g * prog);
    res.b = c1.b + (diff_b * prog);
    res.a = c1.a + (diff_a * prog);
    return res;
}

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight)
{
    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.
    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;
    bool horizontalSpacing = true;

    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );

    return view;
}

void modulateSound(sf::Sound* sound, float lowest, float highest)
{
    sound->setPitch(((float)randomNumber(lowest * 100, highest * 100) / 100));
}

float getMin(float a, float b)
{
    if (a > b)
        return b;
    return a;
}

float getMax(float a, float b)
{
    if (a < b)
        return b;
    return a;
}

void updateTextInputBox(Event& event, EText& inputBox)
{
    if (event.type == Event::TextEntered &&
        event.key.code != 8 &&
        !Keyboard::isKeyPressed(Keyboard::Enter)) {
        if (event.text.unicode < 128) {
            inputBox.setString(inputBox.getString() + event.text.unicode);
        }
    }
    if (event.type == Event::TextEntered &&
        event.key.code == 8) {
        std::string str = inputBox.getString();
        if (str.size() > 0)
            str.pop_back();
        inputBox.setString(str);
    }
}
