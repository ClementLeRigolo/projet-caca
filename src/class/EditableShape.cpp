#include "class/EditableShape.hpp"
#include "class/Game.hpp"

EditableShape::EditableShape(ITexture* texture, Vector2f pos, Vector2f size, bool resizable)
{
    static int index = 0;
    FloatRect bound;

    m_offset = Vector2f(0, 0);
    setSize(size);
    setTexture(texture);
    setOrigin(Vector2f(getSize().x, getSize().y));
    setTextureRect(IntRect(m_offset.x / 2, 0, getSize().x, getSize().y));
    setScale(3.0, 3.0);
    setPosition(pos.x + (getGlobalBounds().width / 2), pos.y + (getGlobalBounds().height / 2));
    m_showResizeHint = false;
    m_grabbed = 0;
    m_hasCollision = false;
    m_layer = 0;
    m_index = index;
    if (texture != NULL)
        m_textureIdentifier = texture->getIdentifier();
    else
        m_textureIdentifier = "NULL";
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
    index++;
}

string EditableShape::getTextureIdentifier() { return m_textureIdentifier; }

int EditableShape::getIndex() { return m_index; }

void EditableShape::resizeHintReposition(float zoomFactor)
{
    FloatRect bound = getGlobalBounds();

    for (auto i : m_resizeHint)
        i.setScale(Vector2f(1.0 * zoomFactor, 1.0 * zoomFactor));
    m_resizeHint[0].setPosition(bound.left, bound.top + (bound.height / 2.0));
    m_resizeHint[1].setPosition(bound.left + bound.width, bound.top + (bound.height / 2.0));
    m_resizeHint[2].setPosition(bound.left + (bound.width / 2.0), bound.top);
    m_resizeHint[3].setPosition(bound.left + (bound.width / 2.0), bound.top + bound.height);
}

void EditableShape::setResizableHintVisible(bool toggled) { m_showResizeHint = toggled; }

void EditableShape::setLayer(int layer) { m_layer = layer; }

int EditableShape::getLayer() const { return m_layer; }

bool EditableShape::comp (const EditableShape* obj, const EditableShape* other) { return (obj->getLayer() < other->getLayer()); }

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
    lastPos = getMousePosition(window);
}

bool EditableShape::hasCollision() { return m_hasCollision; }

void EditableShape::dragResize(RenderWindow& window)
{
    FloatRect bound;
    static Vector2i lastPos = getMousePosition(window);
    Vector2f diff = vectSub(Vector2f(getMousePosition(window)), (Vector2f)lastPos);
    Vector2f newSize = getSize();
    static Vector2u grabbed = Vector2u(1, 3);

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
            else if (m_grabbed == 1 && m_resizeHint[0].getPosition().x + diff.x\
                < getGlobalBounds().left + getGlobalBounds().width) {
                setSize(Vector2f(newSize.x - (diff.x / 3), newSize.y));
                setOrigin(Vector2f(getSize().x, getOrigin().y));
                if (grabbed.x == 2)
                    setPosition(getPosition().x + (getSize().x * 3), getPosition().y);
                grabbed.x = 1;
                m_offset.x += ((diff.x / 6));
                setTextureRect(IntRect(m_offset.x / 2, getTextureRect().top, getSize().x, getSize().y));
            } else if (m_grabbed == 2 && m_resizeHint[1].getPosition().x + diff.x > getGlobalBounds().left) {
                setSize(Vector2f(newSize.x + (diff.x / 3), newSize.y));
                setOrigin(Vector2f(0, getOrigin().y));
                if (grabbed.x == 1)
                    setPosition(getPosition().x - (getSize().x * 3), getPosition().y);
                grabbed.x = 2;
                setTextureRect(IntRect(m_offset.x / 2, getTextureRect().top, getSize().x, getSize().y));
            } else if (m_grabbed == 3 && m_resizeHint[2].getPosition().y + diff.y\
                < getGlobalBounds().top + getGlobalBounds().height) {
                setSize(Vector2f(newSize.x, newSize.y - (diff.y / 3)));
                setOrigin(Vector2f(getOrigin().x, getSize().y));
                if (grabbed.y == 4)
                    setPosition(getPosition().x, getPosition().y + (getSize().y * 3));
                grabbed.y = 3;
                m_offset.y += ((diff.y / 6));
                setTextureRect(IntRect(getTextureRect().left, m_offset.y / 2, getSize().x, getSize().y));


            } else if (m_grabbed == 4 && m_resizeHint[3].getPosition().y + diff.y > getGlobalBounds().top) {
                setSize(Vector2f(newSize.x, newSize.y + (diff.y / 3)));
                setOrigin(Vector2f(getOrigin().x, 0));
                if (grabbed.y == 3)
                    setPosition(getPosition().x, getPosition().y - (getSize().y * 3));
                grabbed.y = 4;
                setTextureRect(IntRect(getTextureRect().left, m_offset.y / 2, getSize().x, getSize().y));
            }
        }
    }
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