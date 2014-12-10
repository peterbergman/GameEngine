#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Engine.h"

using namespace std;

Engine* game_engine = new Engine("My Game", 60, 800, 600);
Sprite* sprite1 = new ImageSprite("/Users/Peter/Documents/DSV/Prog3/images/snowman.png", 30, 30, 200, 256);
//Sprite* sprite2 = new ImageSprite("/Users/Peter/Documents/DSV/Prog3/images/include.png", 500, 30, 163, 80);


void CollisionListener(Sprite* sprite1, Sprite* sprite2) {
    //cout << "Collision detected!\n";
    //game_engine->RemoveSprite(sprite1);
    //game_engine->RemoveSprite(sprite2);
}

void SpriteL1istener(SDL_Event event, Sprite* sprite) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        cout << "click!\n";
    } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                sprite->SetY(sprite->GetY() - 20);
                break;
            case SDLK_DOWN:
                sprite->SetY(sprite->GetY() + 20);
                break;
            case SDLK_LEFT:
                sprite->SetX(sprite->GetX() - 20);
                break;
            case SDLK_RIGHT:
                sprite->SetX(sprite->GetX() + 20);
                break;
            default:
                break;
        }
    }
}

void Sprite1TimeListener(SDL_Event event, Sprite* sprite) {
    sprite->SetX(sprite->GetX()+1);
}

void Sprite2TimeListener(SDL_Event event, Sprite* sprite) {
    sprite->SetX(sprite->GetX()-1);
}

void SnowflakeTimeListener(SDL_Event event, Sprite* sprite) {
    sprite->SetY(sprite->GetY() + 5);
}

void TimeEventListener(SDL_Event event) {
    // create a new sprite with y = 0 and x = random between 0 and the width of the window
    // increase the y coordinate of the sprite with 5
    // set the new sprite time event listener to Sprite3TimeListener with random delay
    int x_pos = rand() % game_engine->GetWindowWidth() + 1;
    int delay = rand() % 50 + 15;
    Sprite* tmpSprite = new ImageSprite("/Users/Peter/Documents/DSV/Prog3/images/snowflake.png", x_pos, 0, 30, 30);
    tmpSprite->AddTimeEventListener(SnowflakeTimeListener, delay);
    game_engine->AddSprite(tmpSprite);
}

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    game_engine->SetScene("/Users/Peter/Documents/DSV/Prog3/images/winter.png");
    
    sprite1->AddActionListener(SpriteL1istener);
    //sprite1->AddTimeEventListener(Sprite1TimeListener, 50);
    game_engine->AddSprite(sprite1);
    
    //sprite2->AddTimeEventListener(Sprite2TimeListener, 50);
    //game_engine->AddSprite(sprite2);
    
    game_engine->AddTimeEventListener(TimeEventListener, 500);
    
    game_engine->SetCollisionListener(CollisionListener);
    
    game_engine->Run();
    delete game_engine;
    return 0;
}
