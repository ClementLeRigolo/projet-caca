#include "class/Render.hpp"

Render::Render()
{
    window = new RenderWindow(VideoMode(960, 540, 32), WINDOW_NAME, Style::Default);
}

Render::~Render()
{
    delete window;
}

void Render::update()
{
    window->clear(Color(50, 50, 50));
    window->display();
}
