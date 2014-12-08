#include "Engine.h"

Uint32 Engine::time_event_type;

Engine::Engine(std::string game_name, int fps) {
    this->fps = fps;
    this->frame_counter = 0;
    window = new Window(game_name, 600, 800);
}

void Engine::AddSprite(Sprite* sprite) {
    window->AddSprite(sprite);
}

void Engine::Quit() {
    is_running = false;
}

void Engine::RegisterTimeEvent() {
    time_event_type = SDL_RegisterEvents(1);
    if (time_event_type != ((Uint32)-1)) {
        SDL_Event time_event;
        SDL_zero(time_event);
        time_event.type = time_event_type;
        time_event.user.code = 0;
        time_event.user.data1 = &fps;
        time_event.user.data2 = &frame_counter;
        SDL_PushEvent(&time_event);
    }
}

void Engine::Run() {
    is_running = true;
    while (is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
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
                    if (event.type == time_event_type) { // TODO: refactor this messy construct if possible
                        window->PropagateEventToSprites(event);
                    }
                    break;
            }
        }
        window->DrawSprites();
        frame_counter++;
        RegisterTimeEvent();
        SDL_Delay(1000 / fps);
    }
}

Engine::~Engine() {
    delete window;
}
