#include "libs.hpp"
#include "class/core.hpp"

int main()
{
    Core core = Core();
    Render* render = core.getRender();

    while (render->window.isOpen()) {
        render->window.display();
    }