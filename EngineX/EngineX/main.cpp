#include <iostream>
#include "Engine.h"

using namespace std;

Engine* game_engine = new Engine("My Game", 20);
Sprite* sprite1 = new ImageSprite("/Users/Peter/Desktop/include.png", 30, 30, 80, 163);
Sprite* sprite2 = new ImageSprite("/Users/Peter/Desktop/include.png", 500, 30, 80, 163);

void CollisionListener(Sprite* sprite1, Sprite* sprite2) {
    cout << "Collision detected!\n";
    game_engine->RemoveSprite(sprite1);
    game_engine->RemoveSprite(sprite2);
}

void SpriteL1istener(SDL_Event event) { // TODO: should maybe get the sprite as well as the event?
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        cout << "click!\n";
    } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                sprite1->SetY(sprite1->GetY() - 10);
                break;
            case SDLK_DOWN:
                sprite1->SetY(sprite1->GetY() + 10);
                break;
            case SDLK_LEFT:
                sprite1->SetX(sprite1->GetX() - 10);
                break;
            case SDLK_RIGHT:
                sprite1->SetX(sprite1->GetX() + 10);
                break;
            default:
                break;
        }
    }
}

void Sprite1TimeListener(SDL_Event event) {
    sprite1->SetX(sprite1->GetX()+1);
}

void Sprite2TimeListener(SDL_Event event) {
    sprite2->SetX(sprite2->GetX()-1);
}

int main(int argc, const char * argv[]) {
    sprite1->AddActionListener(SpriteL1istener);
    sprite1->AddTimeEventListener(Sprite1TimeListener, 50);
    game_engine->AddSprite(sprite1);
    
    sprite2->AddTimeEventListener(Sprite2TimeListener, 50);
    game_engine->AddSprite(sprite2);
    
    game_engine->SetCollisionListener(CollisionListener);
    
    game_engine->Run();
    delete game_engine;
    return 0;
}
