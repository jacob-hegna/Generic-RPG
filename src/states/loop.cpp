#include "loop.h"

Gamestates gamestates = GAMEPLAY;

int loop(Window *window) {

    Engine **engine = new Engine*;
    for(int i = 0; i < stateAmt; ++i) {
        engine[i] = new Engine();
    }

    engine[GAMEPLAY]->init(window, Gameplay::init, Gameplay::logic, Gameplay::render, Gameplay::free, "Gameloop");

    while(!window->shouldClose()) {   
        const Uint8* keystate = SDL_GetKeyboardState(NULL);

        engine[gamestates]->exec();

        if(window->getEvent()->type == SDL_QUIT || keystate[SDL_GetScancodeFromKey(SDLK_ESCAPE)]) {
            window->close();
        }
        window->update();
    }

    delete engine;

    return 0;
}