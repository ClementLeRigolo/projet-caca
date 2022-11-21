#pragma once

#include "libs.hpp"

class EditableShape : public RectangleShape
{
    private:
        RectangleShape m_resizeHint[4];
        bool m_showResizeHint;
        int m_grabbed;
    public:
        EditableShape(Texture* texture, Vector2f pos, Vector2f size);
        void dragResize(RenderWindow& window);
        void dragMove(RenderWindow& window);
        void setResizableHintVisible(bool toggle);
        void resizeHintReposition(float zoomFactor);
        void draw(RenderTarget &target);
};