#include "Engine.h"

Engine::Engine(std::string game_name) {
    window = new Window(game_name, 600, 800);
}

void Engine::AddSprite(Sprite* sprite) {
    window->AddSprite(sprite);
}

void Engine::Quit() {
    is_running = false;
}

void Engine::Run() {
    is_running = true;
    while (is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    window->PropagateEventToSprites(event);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                case SDL_MOUSEWHEEL:
                    window->PropagateEventToSprites(event);
                    break;
                case SDL_QUIT:
                    Quit();
                    break;
                default:
                    break;
            }
        }
        window->DrawSprites();
        SDL_Delay(50);
    }
}

Engine::~Engine() {
    delete window;
}
