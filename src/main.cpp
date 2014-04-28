#include "window/window.h"
#include "states/loop.h"

// globals.h definitions
bool loopQuit = false;

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
    AllocConsole();
    freopen("conin$", "r", stdin);
    freopen("conout$", "w", stdout);
    freopen("conout$", "w", stderr);
    Window::initSDL();
    Window *window = new Window();
    window->init();

    loop(window);

    Window::deinitSDL();
    return 0;
}