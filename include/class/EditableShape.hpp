#pragma once

#include "libs.hpp"
#include "class/ITexture.hpp"

class EditableShape : public RectangleShape
{
    private:
        int m_index;
        int m_layer;
        RectangleShape m_resizeHint[4];
        bool m_showResizeHint;
        int m_grabbed;
        bool m_hasCollision;
        string m_textureIdentifier;
        Vector2f m_offset;
        Vector2u m_grabbedSide;

    public:
        static bool comp (const EditableShape* obj, const EditableShape* other);
        EditableShape(ITexture* texture, Vector2f pos, Vector2f size, bool hasCollision);
        bool hasCollision();
        int getIndex();
        string getTextureIdentifier();
        void setLayer(int layer);
        int getLayer() const;
        void dragResize(RenderWindow& window);
        void dragMove(RenderWindow& window);
        void setResizableHintVisible(bool toggle);
        void resizeHintReposition(float zoomFactor);
        void draw(RenderTarget &target);
};