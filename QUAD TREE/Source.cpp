#include "Application.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "QUAD TREE");
    window.setMouseCursorVisible(false);

    Application application(&window);

    application.run();

    return 0;
}