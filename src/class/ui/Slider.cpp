#include "class/ui/Slider.hpp"
#include "class/system/Logger.hpp"
#include "class/system/Settings.hpp"

Slider::Slider() { m_progress = 0; };

Slider::Slider(Texture* outTexture, Texture* inTexture,
Texture* sliderThingyTexture, Vector2f size, Vector2f pos, bool vertical)
{
    m_progress = 0.5;
    m_grabbed = false;

    getInShape().setSize(Vector2f(outTexture->getSize().x * 0.83, outTexture->getSize().y * 3));
    getInShape().setOrigin(getCenter(getInShape()));
    getInShape().setTexture(inTexture);
    getInShape().setPosition(pos);
    getInShape().setOutlineColor(Color(255, 0, 0, 150));

    getOutShape().setSize(Vector2f(outTexture->getSize()));
    getOutShape().setOrigin(getCenter(getOutShape()));
    getOutShape().setTexture(outTexture);
    getOutShape().setPosition(pos);

    getSliderThingy().setSize(Vector2f(sliderThingyTexture->getSize()));
    getSliderThingy().setOrigin(getCenter(getSliderThingy()));
    getSliderThingy().setTexture(sliderThingyTexture);
    getSliderThingy().setPosition(pos);

    if (vertical) {
       getOutShape().setRotation(90);
       getInShape().setRotation(90);
       getSliderThingy().setRotation(90);
    }

    setScale(Vector2f(1.5, 1.5));

    m_thingyBaseScale = Vector2f(2, 2);
};

RectangleShape& Slider::getOutShape()
{
    return m_outShape;
}

RectangleShape& Slider::getInShape()
{
    return m_inShape;
}

RectangleShape& Slider::getSliderThingy()
{
    return m_sliderThingy;
}

float Slider::getProgress() const
{
    return m_progress;
}

void Slider::setProgress(float progress)
{
    m_progress = progress;
}

void Slider::setPosition(Vector2f pos)
{
    getOutShape().setPosition(pos);
    getInShape().setPosition(pos);
    getSliderThingy().setPosition(pos);
}

void Slider::setScale(Vector2f scale)
{
    getInShape().setScale(scale);
    getOutShape().setScale(scale);
    getSliderThingy().setScale(vectFmult(scale, m_thingyBaseScale));
}

void Slider::setSize(Vector2f size)
{
    getInShape().setSize(size);
    getOutShape().setSize(Vector2f(size.x, size.y));
    getSliderThingy().setSize(Vector2f(size.y, size.y));
}

bool Slider::isGrabbed()
{
    return m_grabbed;
}

void Slider::update(RenderWindow& window)
{
    Vector2i mousePos = getMousePosition(window);
    FloatRect boundOut = getInShape().getGlobalBounds();
    FloatRect bound = getSliderThingy().getGlobalBounds();
    Vector2f diff;

    boundOut.left -= boundOut.width / 5.0;
    boundOut.width += boundOut.width / 2.5;
    boundOut.top -= boundOut.height / 3.0;
    boundOut.height += boundOut.height / 1.5;

    if (!DoMouseIntersect(mousePos, boundOut)) {
        m_grabbed = false;
        getSliderThingy().setScale(m_thingyBaseScale);
        return;
    }
    if (DoMouseIntersect(mousePos, bound)) {
        getSliderThingy().setScale(Vector2f(m_thingyBaseScale.x + 0.1, m_thingyBaseScale.y + 0.1));
        if (Mouse::isButtonPressed(Mouse::Left) && !m_grabbed) {
            m_lastMousePos = mousePos;
            m_grabbed = true;
        } else if (!Mouse::isButtonPressed(Mouse::Left))
            m_grabbed = false;
    } else if (!Mouse::isButtonPressed(Mouse::Left)) {
        getSliderThingy().setScale(m_thingyBaseScale);
        m_grabbed = false;
    }
    if (m_grabbed) {
        getSliderThingy().setScale(Vector2f(m_thingyBaseScale.x - 0.1, m_thingyBaseScale.y - 0.1));
        diff = Vector2f(mousePos.x - m_lastMousePos.x,
        mousePos.y - m_lastMousePos.y);
        diff.y = 0;
        if ((mousePos.x >= getSliderThingy().getGlobalBounds().left && diff.x > 0)
            || (mousePos.x <= getSliderThingy().getGlobalBounds().left\
            + getSliderThingy().getGlobalBounds().width && diff.x < 0)) {
            getSliderThingy().setPosition(getSliderThingy().getPosition() + diff);
            if (getSliderThingy().getPosition().x > (getInShape().getGlobalBounds().left\
            + getInShape().getGlobalBounds().width))
                getSliderThingy().setPosition(Vector2f(getInShape().getGlobalBounds().left\
                + getInShape().getGlobalBounds().width, getSliderThingy().getPosition().y));
            else if (getSliderThingy().getPosition().x < getInShape().getGlobalBounds().left)
                getSliderThingy().setPosition(Vector2f(getInShape().getGlobalBounds().left,
                getSliderThingy().getPosition().y));
        }
        m_lastMousePos = mousePos;
        m_progress = distFrom(getSliderThingy().getPosition(),
        Vector2f(getInShape().getGlobalBounds().left,
        getSliderThingy().getPosition().y)) / getInShape().getGlobalBounds().width;
    } 
}

void Slider::limit(float limit, bool keepValue)
{
    if (m_progress > limit) {
        if (!keepValue)
            m_progress = limit;
        getSliderThingy().setPosition(Vector2f(getInShape().getGlobalBounds().left\
        + (getInShape().getGlobalBounds().width * limit),
        getSliderThingy().getPosition().y));
    }
}

void Slider::draw(sf::RenderTarget &target)
{
    target.draw(m_outShape);
    target.draw(m_inShape);
    target.draw(m_sliderThingy);
}
