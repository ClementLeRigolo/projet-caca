#include "class/EditableShape.hpp"
#include "class/Game.hpp"

EditableShape::EditableShape(ITexture* texture, Vector2f pos, Vector2f size)
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
    m_grabbedSide = Vector2u(1, 3);
    m_baseColor = sf::Color::White;
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

EditableHitbox::EditableHitbox(Vector2f pos, Vector2f size)
: EditableShape(NULL, pos, size)
{
    setFillColor(sf::Color(255, 0, 0, 100));
    m_baseColor = getFillColor();
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

void EditableShape::setBaseColor(sf::Color baseColor) { m_baseColor = baseColor; }

bool EditableShape::comp(const EditableShape* obj, const EditableShape* other) { return (obj->getLayer() < other->getLayer()); }

void EditableShape::dragMove(RenderWindow& window, float zoom)
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
    static bool moveLeft = false;
    static bool moveRight = false;
    static bool moveDown = false;
    static bool moveUp = false;
    if (!m_grabbed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && moveLeft) {
            move(-5 * zoom, 0);
            moveLeft = false;
            return;
        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            moveLeft = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && moveRight) {
            move(5 * zoom, 0);
            moveRight = false;
            return;
        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            moveRight = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && moveUp) {
            move(0, -5 * zoom);
            moveUp = false;
            return;
        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            moveUp = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && moveDown) {
            move(0, 5 * zoom);
            moveDown = false;
            return;
        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            moveDown = true;
    }
}

sf::Color EditableShape::getBaseColor() const { return m_baseColor; } ;

bool EditableShape::hasCollision() const { return false; }

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
            else if (m_grabbed == 1 && m_resizeHint[0].getPosition().x + diff.x\
                < getGlobalBounds().left + getGlobalBounds().width) {
                setSize(Vector2f(newSize.x - (diff.x / 3), newSize.y));
                setOrigin(Vector2f(getSize().x, getOrigin().y));
                if (m_grabbedSide.x == 2)
                    setPosition(getPosition().x + (getSize().x * 3), getPosition().y);
                m_grabbedSide.x = 1;
                m_offset.x += ((diff.x / 6));
                setTextureRect(IntRect(m_offset.x / 2, getTextureRect().top, getSize().x, getSize().y));
            } else if (m_grabbed == 2 && m_resizeHint[1].getPosition().x + diff.x > getGlobalBounds().left) {
                setSize(Vector2f(newSize.x + (diff.x / 3), newSize.y));
                setOrigin(Vector2f(0, getOrigin().y));
                if (m_grabbedSide.x == 1)
                    setPosition(getPosition().x - (getSize().x * 3), getPosition().y);
                m_grabbedSide.x = 2;
                setTextureRect(IntRect(m_offset.x / 2, getTextureRect().top, getSize().x, getSize().y));
            } else if (m_grabbed == 3 && m_resizeHint[2].getPosition().y + diff.y\
                < getGlobalBounds().top + getGlobalBounds().height) {
                setSize(Vector2f(newSize.x, newSize.y - (diff.y / 3)));
                setOrigin(Vector2f(getOrigin().x, getSize().y));
                if (m_grabbedSide.y == 4)
                    setPosition(getPosition().x, getPosition().y + (getSize().y * 3));
                m_grabbedSide.y = 3;
                m_offset.y += ((diff.y / 6));
                setTextureRect(IntRect(getTextureRect().left, m_offset.y / 2, getSize().x, getSize().y));


            } else if (m_grabbed == 4 && m_resizeHint[3].getPosition().y + diff.y > getGlobalBounds().top) {
                setSize(Vector2f(newSize.x, newSize.y + (diff.y / 3)));
                setOrigin(Vector2f(getOrigin().x, 0));
                if (m_grabbedSide.y == 3)
                    setPosition(getPosition().x, getPosition().y - (getSize().y * 3));
                m_grabbedSide.y = 4;
                setTextureRect(IntRect(getTextureRect().left, m_offset.y / 2, getSize().x, getSize().y));
            }
        }
    }
    lastPos = getMousePosition(window);
}

void EditableShape::init()
{
    setTextureRect(IntRect(m_offset.x / 2, getTextureRect().top, getSize().x, getSize().y));
}

RectangleShape* EditableShape::getResizeHints()
{
    return m_resizeHint;
}

Vector2f EditableShape::getOffset() const
{
    return m_offset;
}

Vector2u EditableShape::getGrabbedSide() const
{
    return m_grabbedSide;
}

void EditableShape::setGrabbedSide(Vector2u GrabbedSide)
{
    m_grabbedSide = GrabbedSide;
}

int EditableShape::getGrabbed() const
{
    return m_grabbed;
}

void EditableShape::setGrabbed(int grabbed)
{
    m_grabbed = grabbed;
}

void EditableShape::setOffset(Vector2f Offset)
{
    m_offset = Offset;
}

void EditableShape::draw(RenderTarget& target)
{
    target.draw(*this);
    if (!m_showResizeHint)
       return;
    for (int i = 0; i < 4; i++)
        target.draw(m_resizeHint[i]);
}

bool EditableHitbox::hasCollision() const { return true; }
