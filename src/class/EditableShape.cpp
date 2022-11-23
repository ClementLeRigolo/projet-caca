#include "class/EditableShape.hpp"
#include "class/Game.hpp"

EditableShape::EditableShape(Texture* texture, Vector2f pos, Vector2f size)
{
    FloatRect bound;
    setSize(size);
    setTextureRect(IntRect(0, 0, size.x, size.y));
    setTexture(texture);
    setOrigin(getCenter(*this));
    setPosition(pos);
    m_showResizeHint = false;
    m_grabbed = 0;

    bound = getGlobalBounds();
    for (int i = 0; i < 4; i++) {
        m_resizeHint[i].setSize(Vector2f(20, 64));
        m_resizeHint[i].setOrigin(getCenter(m_resizeHint[i]));
        m_resizeHint[i].setTexture(&GET_TEXTURE(E_RESIZE_HINT));
    }
    m_resizeHint[0].setPosition(bound.left, bound.top + (bound.height / 2.0));
    m_resizeHint[0].setRotation(90);
    m_resizeHint[1].setPosition(bound.left + bound.width, bound.top + (bound.height / 2.0));
    m_resizeHint[1].setRotation(90);
    m_resizeHint[2].setPosition(bound.left + (bound.width / 2.0), bound.top);
    m_resizeHint[3].setPosition(bound.left + (bound.width / 2.0), bound.top + bound.height);

    setTextureRect(IntRect((-getSize().x / 2.0) + getPosition().x, (-getSize().y / 2.0) +  + getPosition().y, getSize().x, getSize().y));
}

void EditableShape::resizeHintReposition(float zoomFactor)
{
    FloatRect bound = getGlobalBounds();

    for (int i = 0; i < 4; i++)
        m_resizeHint[i].setScale(Vector2f(1.0 * zoomFactor, 1.0 * zoomFactor));
    m_resizeHint[0].setPosition(bound.left, bound.top + (bound.height / 2.0));
    m_resizeHint[1].setPosition(bound.left + bound.width, bound.top + (bound.height / 2.0));
    m_resizeHint[2].setPosition(bound.left + (bound.width / 2.0), bound.top);
    m_resizeHint[3].setPosition(bound.left + (bound.width / 2.0), bound.top + bound.height);
}

void EditableShape::setResizableHintVisible(bool toggled)
{
    m_showResizeHint = toggled;
}

void EditableShape::dragMove(RenderWindow& window)
{
    FloatRect bound = getGlobalBounds();
    static Vector2i lastPos = getMousePosition(window);
    Vector2f diff = vectSub(Vector2f(getMousePosition(window)), (Vector2f)lastPos);

    if (DoMouseIntersect(getMousePosition(window), bound) && m_grabbed == 0) {
        if (Mouse::isButtonPressed(Mouse::Left))
            m_grabbed = true;
        else
            m_grabbed = false;
    }
    if (m_grabbed) {
        if (!Mouse::isButtonPressed(Mouse::Left))
            m_grabbed = false;
        move(diff);
    }
    setTextureRect(IntRect((-getSize().x / 2.0) + getPosition().x, (-getSize().y / 2.0) +  + getPosition().y, getSize().x, getSize().y));
    lastPos = getMousePosition(window);
}

void EditableShape::dragResize(RenderWindow& window)
{
    FloatRect bound;
    static Vector2i lastPos = getMousePosition(window);
    Vector2f diff = vectSub(Vector2f(getMousePosition(window)), (Vector2f)lastPos);
    Vector2f newSize = getSize();

    for (int i = 0; i < 4; i++) {
        bound = m_resizeHint[i].getGlobalBounds();
        if (DoMouseIntersect(getMousePosition(window), bound) && m_grabbed == 0) {
            m_resizeHint[i].setFillColor(Color::Green);
            if (Mouse::isButtonPressed(Mouse::Left))
                m_grabbed = i + 1;
            else
                m_grabbed = 0;
        } else if (i + 1 != m_grabbed) {
            m_resizeHint[i].setFillColor(Color::White);
        }
        if (m_grabbed > 0) {
            if (!Mouse::isButtonPressed(Mouse::Left))
                m_grabbed = 0;
            else if (m_grabbed == 1 && m_resizeHint[0].getPosition().x + diff.x < getGlobalBounds().left + getGlobalBounds().width)
                setSize(Vector2f(newSize.x - diff.x, newSize.y));
            else if (m_grabbed == 2 && m_resizeHint[1].getPosition().x + diff.x > getGlobalBounds().left)
                setSize(Vector2f(newSize.x + diff.x, newSize.y));
            else if (m_grabbed == 3 && m_resizeHint[2].getPosition().y + diff.y < getGlobalBounds().top + getGlobalBounds().height)
                setSize(Vector2f(newSize.x, newSize.y - diff.y));
            else if (m_grabbed == 4 && m_resizeHint[3].getPosition().y + diff.y > getGlobalBounds().top)
                setSize(Vector2f(newSize.x, newSize.y + diff.y));
        }
    }
    setOrigin(getCenter(*this));
    setTextureRect(IntRect((-getSize().x / 2.0) + getPosition().x, (-getSize().y / 2.0) +  + getPosition().y, getSize().x, getSize().y));
    lastPos = getMousePosition(window);
}

void EditableShape::draw(RenderTarget& target)
{
    target.draw(*this);
    if (!m_showResizeHint)
       return;
    for (int i = 0; i < 4; i++)
        target.draw(m_resizeHint[i]);
}