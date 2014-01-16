#include "loop.h"

Gamestates gamestates = GAMEPLAY;

int loop(Window *window) {

    Engine **engine = new Engine*;
    for(int i = 0; i < stateAmt; ++i) {
        engine[i] = new Engine();
    }

    engine[GAMEPLAY]->init(window, Gameplay::init, Gameplay::logic, Gameplay::render, Gameplay::free, "Gameloop");

    while(!window->shouldClose()) {        
        engine[gamestates]->exec();

        if(window->getEvent()->type == SDL_QUIT) {
            window->close();
        }
        window->update();
    }

    delete engine;

    return 0;
}