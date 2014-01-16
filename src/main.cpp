#include "window/window.h"
#include "states/loop.h"


#ifdef _WIN32
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                     int nCmdShow)
#else
int main(int argc, char *argv[])
#endif
{
    Window::initSDL();
    Window *window = new Window();
    window->init();

    loop(window);

    Window::deinitSDL();
    return 0;
}