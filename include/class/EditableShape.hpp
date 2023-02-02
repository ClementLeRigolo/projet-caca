#pragma once

#include "libs.hpp"
#include "class/ITexture.hpp"

class EditableShape : public RectangleShape
{
    protected:
        int m_index;
        int m_layer;
        RectangleShape m_resizeHint[4];
        bool m_showResizeHint;
        int m_grabbed;
        string m_textureIdentifier;
        Vector2f m_offset;
        Vector2u m_grabbedSide;
        sf::Color m_baseColor;

    public:
        static bool comp(const EditableShape* obj, const EditableShape* other);
        EditableShape(ITexture* texture, Vector2f pos, Vector2f size);
        virtual bool hasCollision() const;
        int getIndex();
        string getTextureIdentifier();
        void setLayer(int layer);
        int getLayer() const;
        void dragResize(RenderWindow& window);
        void dragMove(RenderWindow& window, float zoom);
        void setResizableHintVisible(bool toggle);
        void resizeHintReposition(float zoomFactor);
        void draw(RenderTarget &target);
        Vector2f getOffset() const;
        Vector2u getGrabbedSide() const;
        int getGrabbed() const;
        void setGrabbed(int grabbed);
        void setGrabbedSide(Vector2u grabbedSide);
        void setOffset(Vector2f offset);
        sf::Color getBaseColor() const;
        void setBaseColor(sf::Color color);
        RectangleShape* getResizeHints();
        void init();
};

class EditableHitbox : public EditableShape
{
    public:
        EditableHitbox(Vector2f pos, Vector2f size);
        bool hasCollision() const override;
};