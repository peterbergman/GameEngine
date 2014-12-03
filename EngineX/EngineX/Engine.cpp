#include "Engine.h"

Engine::Engine() {
    window = new Window(600, 800);
    Run();
}

void Engine::Run() {
    is_running = true;
    while (is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    is_running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        is_running = false;
                    }
                default:
                    break;
            }
        }
    }
}

Engine::~Engine() {
    delete window;
}

