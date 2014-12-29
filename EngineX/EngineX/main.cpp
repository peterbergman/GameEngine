#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Engine.h"

using namespace std;

Engine* game_engine = new Engine("My Game", 60, 800, 600);
Sprite* snowman1 = AnimatedSprite::GetInstance({"/Users/Peter/Documents/DSV/Prog3/images/snowman.png",
                                                "/Users/Peter/Documents/DSV/Prog3/images/snowman2.png"},
                                               500, 30, 270, 200, 256);
Sprite* snowman2 = StaticSprite::GetInstance("/Users/Peter/Documents/DSV/Prog3/images/snowman.png", 500, 270, 200, 256);
Sprite* ground = StaticSprite::GetInstance("/Users/Peter/Documents/DSV/Prog3/images/ground.png", 0, 513, 1024, 87);

// Jump stuff
double vi = -200, t = 0;
double g = 200;
bool is_jumping = false;


void CollisionListener(Sprite* sprite1, Sprite* sprite2) {
    if (sprite1 == snowman1 && sprite2 == snowman2) {
        cout << "Collision detected!\n";
        game_engine->RemoveSprite(sprite1);
        game_engine->RemoveSprite(sprite2);
    }
}

void Jump(SDL_Event event, Sprite* sprite) {
    if (is_jumping) {
        sprite->SetY((vi * t + g * t * t / 2) + 270);
        t = t + (game_engine->GetTimeElapsed() / 1000) + 0.04;
        
        if (sprite->GetY() > 270) {
            t = 0;
            is_jumping = false;
        }
    }
}

void Snowman1Listener(SDL_Event event, Sprite* sprite) {
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
            case SDLK_SPACE:
                is_jumping = true;
                sprite->AddTimeEventListener(Jump, 0);
            default:
                break;
        }
    }
}

void SnowmanRightMove(SDL_Event event, Sprite* sprite) {
    sprite->SetX(sprite->GetX() + 5);
}

void SnowmanLeftMove(SDL_Event event, Sprite* sprite) {
    sprite->SetX(sprite->GetX() - 5);
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
    Sprite* tmpSprite = MovingSprite::GetInstance("/Users/Peter/Documents/DSV/Prog3/images/snowflake.png", x_pos, 0, 30, 30, 0, 1);
    //tmpSprite->AddTimeEventListener(SnowflakeTimeListener, delay);
    game_engine->AddSprite(tmpSprite);
}

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    game_engine->SetScene("/Users/Peter/Documents/DSV/Prog3/images/winter.png");
    snowman1->AddActionListener(Snowman1Listener);
    game_engine->AddSprite(snowman1);
    game_engine->AddSprite(snowman2);
    game_engine->AddSprite(ground);
    game_engine->AddTimeEventListener(TimeEventListener, 500);
    game_engine->SetCollisionListener(CollisionListener);
    
    game_engine->Run();
    delete game_engine;
    return 0;
}
