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
                case SDL_QUIT:
                    Quit();
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        Quit();
                    }
                default:
                    break;
            }
        }
        SDL_RenderClear(window->GetRenderer());
        window->DrawSprites();
        SDL_RenderPresent(window->GetRenderer());
        SDL_Delay(50);
    }
}

Engine::~Engine() {
    delete window;
}
