#include "Engine.h"

void Engine::run() {
    while (is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    is_running = false;
                    break;
                default:
                    break;
            }
        }
    }
}