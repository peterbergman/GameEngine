#include <iostream>
#include "Engine.h"

using namespace std;

Sprite* sprite = new ImageSprite("/Users/Peter/Desktop/include.png", 30, 30, 80, 163);

void SpriteListener(SDL_Event event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        cout << "click!\n";
    } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                sprite->SetY(sprite->GetY() - 10);
                break;
            case SDLK_DOWN:
                sprite->SetY(sprite->GetY() + 10);
                break;
            case SDLK_LEFT:
                sprite->SetX(sprite->GetX() - 10);
                break;
            case SDLK_RIGHT:
                sprite->SetX(sprite->GetX() + 10);
                break;
            default:
                break;
        }
    }
}

void SpriteTimeListener(SDL_Event event) {
    std::cout << "Found time event listener!\n";
}

int main(int argc, const char * argv[]) {
    Engine* game_engine = new Engine("My Game", 1);
    sprite->AddActionListener(SpriteListener);
    sprite->AddTimeEventListener(SpriteTimeListener, 100);
    game_engine->AddSprite(sprite);
    game_engine->Run();
    delete game_engine;
    return 0;
}
