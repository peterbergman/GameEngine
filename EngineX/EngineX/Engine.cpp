#include "Engine.h"

Uint32 Engine::time_event_type;

Engine::Engine(std::string game_name, int fps, int window_width, int window_height) {
    this->fps = fps;
    this->frame_counter = 0;
    window = new Window(game_name, window_width, window_height);
}

void Engine::AddSprite(Sprite* sprite) {
    window->AddSprite(sprite);
}

void Engine::RemoveSprite(Sprite* sprite) {
    window->RemoveSprite(sprite);
}

void Engine::SetCollisionListener(collision_listener listener) {
    current_collision_listener = listener;
}

int Engine::GetWindowWidth() {
    return window->GetWidth();
}

int Engine::GetWindowHeight() {
    return window->GetHeight();
}

void Engine::AddTimeEventListener(time_event_listener listener, int delay) {
    time_event_listeners[delay] = listener;
}

void Engine::SetScene(std::string scene_background) {
    window->SetBackground(scene_background);
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

void Engine::DetectCollision() { // TODO: improve the collision detection algorithm
    for (Sprite* sprite : window->GetSprites()) {
        for (Sprite* other_sprite : window->GetSprites()) {
            if (sprite != other_sprite && sprite->Contains(other_sprite)) {
                if (current_collision_listener != nullptr) {
                    current_collision_listener(sprite, other_sprite);
                }
            }
        }
    }
}

void Engine::HandleTimeEvent(SDL_Event event) {
    for (std::pair<const int, time_event_listener>& entry : time_event_listeners) {
        int fps = *((int*)event.user.data1);
        int frame_counter = *((int*)event.user.data2);
        int rhs = (int)(round(((fps / 1000.0 ) * entry.first)));
        if (rhs > 0) {
            int result = frame_counter % rhs;
            if (result == 0) {
                entry.second(event);
            }
        } else {
            entry.second(event);
        }
    }
}

void Engine::PollEvent() {
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
                    HandleTimeEvent(event);
                }
                break;
        }
    }
}

void Engine::Run() {
    is_running = true;
    while (is_running) {
        PollEvent();
        window->DrawSprites();
        frame_counter++;
        RegisterTimeEvent();
        DetectCollision();
        SDL_Delay(1000 / fps);
    }
}

Engine::~Engine() {
    delete window;
}
