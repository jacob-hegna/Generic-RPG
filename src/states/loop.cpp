#include "loop.h"
#include "../globals.h"

Gamestates gamestates = GAMEPLAY;

int loop(Window *window) {

    Engine **engine = new Engine*;
    for(int i = 0; i < stateAmt; ++i) {
        engine[i] = new Engine();
    }

    engine[GAMEPLAY]->init(window, Gameplay::init, Gameplay::logic, Gameplay::render, Gameplay::free, "Gameloop");
    engine[PAUSEMENU]->init(window, PauseMenu::init, PauseMenu::logic, PauseMenu::render, PauseMenu::free, "Pause Menu");

    while(!window->shouldClose() && !loopQuit) {   
        const Uint8* keystate = SDL_GetKeyboardState(NULL);

        engine[gamestates]->exec();

        if(keystate[SDL_GetScancodeFromKey(SDLK_ESCAPE)]) {
            switch(gamestates) {
            case GAMEPLAY:
                gamestates = PAUSEMENU;
                break;
            case PAUSEMENU:
                gamestates = GAMEPLAY;
                break;
            }
        }

        if(window->getEvent()->type == SDL_QUIT) {
            window->close();
        }
        window->update();
    }
    foo[0] = 10;

    return 0;
}