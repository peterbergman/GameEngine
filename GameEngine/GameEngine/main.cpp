#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Engine.h"

using namespace std;

Engine* game_engine = new Engine("My Game", 60, 800, 640);
Level* level1 = new Level(5);
Level* level2 = new Level(10);
Sprite* snowman1 = AnimatedSprite::GetInstance({"/Users/Peter/Documents/DSV/Prog3/images/snowman.png",
                                                "/Users/Peter/Documents/DSV/Prog3/images/snowman2.png"},
                                               500, 30, 310, 200, 256);
Sprite* snowman2 = StaticSprite::GetInstance("/Users/Peter/Documents/DSV/Prog3/images/snowman.png", 500, 310, 200, 256);
Sprite* ground = StaticSprite::GetInstance("/Users/Peter/Documents/DSV/Prog3/images/ground.png", 0, 553, 1024, 87);

// Jump stuff
double vi = -200, t = 0;
double g = 200;
bool is_jumping = false;


void CollisionListener(Sprite* sprite1, Sprite* sprite2) {
    if (sprite1 == snowman1 && sprite2 == snowman2) {
        cout << "Collision detected!\n";
        level1->RemoveSprite(sprite1);
        level1->RemoveSprite(sprite2);
    }
}

void Jump(Sprite* sprite) {
    if (is_jumping) {
        sprite->SetY((vi * t + g * t * t / 2) + 310);
        t = t + (game_engine->GetTimeElapsed() / 1000) + 0.04;
        
        if (sprite->GetY() > 310) {
            t = 0;
            is_jumping = false;
        }
    }
}

void SnowmanRightMove(Sprite* sprite) {
    sprite->SetX(sprite->GetX() + 20);
}

void SnowmanLeftMove(Sprite* sprite) {
    sprite->SetX(sprite->GetX() - 20);
}

void SnowmanJump(Sprite* sprite) {
    is_jumping = true;
    sprite->AddTimeListener(Jump, 0);
}

void SnowmanClick(Sprite* sprite) {
    cout << "Click!" << endl;
}

void SnowflakeTimeListener(Sprite* sprite) {
    sprite->SetY(sprite->GetY() + 5);
}

void GameEventListener() {
    cout << "Game listener!" << endl;
}

void SetLevel1() {
    game_engine->SetCurrentLevel(level1);
}

void SetLevel2() {
    game_engine->SetCurrentLevel(level2);
}

void TimeEventListener() {
    // create a new sprite with y = 0 and x = random between 0 and the width of the window
    // increase the y coordinate of the sprite with 5
    // set the new sprite time event listener to Sprite3TimeListener with random delay
    int x_pos = rand() % game_engine->GetWindowWidth() + 1;
    int delay = rand() % 50 + 15;
    Sprite* tmpSprite = MovingSprite::GetInstance("/Users/Peter/Documents/DSV/Prog3/images/snowflake.png", x_pos, 0, 30, 30, 0, 1);
    //tmpSprite->AddTimeEventListener(SnowflakeTimeListener, delay);
    level1->AddSprite(tmpSprite);
}

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    
    snowman1->AddEventListener(SnowmanRightMove, SDLK_RIGHT);
    snowman1->AddEventListener(SnowmanLeftMove, SDLK_LEFT);
    snowman1->AddEventListener(SnowmanJump, SDLK_SPACE);
    snowman1->AddEventListener(SnowmanClick, SDL_MOUSEBUTTONDOWN);
    
    level1->AddTimeListener(TimeEventListener, 500);
    game_engine->SetCollisionListener(CollisionListener);
    game_engine->AddEventListener(GameEventListener, SDLK_RETURN);
    game_engine->AddEventListener(SetLevel1, SDLK_1);
    game_engine->AddEventListener(SetLevel2, SDLK_2);

    level1->SetBackground("/Users/Peter/Documents/DSV/Prog3/images/winter.png");
    level1->AddSprite(snowman1);
    level1->AddSprite(snowman2);
    level1->AddSprite(ground);
    game_engine->AddLevel(level1);
    
    level2->SetBackground("/Users/Peter/Documents/DSV/Prog3/images/winter2.png");
    game_engine->AddLevel(level2);
    
    game_engine->SetCurrentLevel(level1);
    game_engine->Run();
    
    delete game_engine;
    return 0;
}
