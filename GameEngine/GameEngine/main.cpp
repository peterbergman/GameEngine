#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Engine.h"

using namespace std;

Engine* game_engine = new Engine("SpaceShooter", 60, 800, 640);
Level* level1 = new Level(5);
Level* level2 = new Level(10);
Sprite* player = AnimatedSprite::GetInstance("player", {"/Users/Peter/Documents/DSV/Prog3/images/space/player_space_ship1.png"},
                                               0, 300, 520, 128, 128);
Sprite* text_input = TextInputSprite::GetInstance("text_input", "enter your name:");

void CollisionListener(Sprite* sprite1, Sprite* sprite2) {
    if ((sprite1->GetTag() == "bullet" && sprite2->GetTag() == "enemy") || (sprite2->GetTag() == "bullet" && sprite1->GetTag() == "enemy")) {
        cout << "Collision detected!\n";
        level1->RemoveSprite(sprite1);
        level1->RemoveSprite(sprite2);
    }
}

void PlayerRightMove(SDL_Event event, Sprite* sprite) {
    sprite->SetX(sprite->GetX() + 20);
}

void PlayerLeftMove(SDL_Event event, Sprite* sprite) {
    sprite->SetX(sprite->GetX() - 20);
}

void EnemyListenerLevel1() {
    int x_pos = rand() % game_engine->GetWindowWidth() + 100;
    if (x_pos < (game_engine->GetWindowWidth() - 100)) {
        int delay = rand() % 50 + 15;
        Sprite* tmpSprite = MovingSprite::GetInstance("enemy" ,"/Users/Peter/Documents/DSV/Prog3/images/space/level1_enemy.png", x_pos, 0, 100, 100, 0, 1);
        level1->AddSprite(tmpSprite);
    }
}

void ShootListenerLevel1() {
    int x_pos = player->GetX();
    Sprite* tmpSprite = MovingSprite::GetInstance("bullet", "/Users/Peter/Documents/DSV/Prog3/images/space/level1_bullet.png", x_pos, 520, 19, 43, 0, -10);
    level1->AddSprite(tmpSprite);
}

void PlayerNameEnteredListener() {
    level1->RemoveSprite(text_input);
    player->AddEventListener(PlayerRightMove, SDLK_RIGHT);
    player->AddEventListener(PlayerLeftMove, SDLK_LEFT);
    
    level1->AddTimeListener(EnemyListenerLevel1, 2000);
    game_engine->SetCollisionListener(CollisionListener);
    game_engine->AddEventListener(ShootListenerLevel1, SDLK_SPACE);
    
    level1->AddSprite(player);
}

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    
    level1->SetBackground("/Users/Peter/Documents/DSV/Prog3/images/space/level1_background.png");
    level1->AddSprite(text_input);
    game_engine->AddEventListener(PlayerNameEnteredListener, SDLK_RETURN);

    
    game_engine->AddLevel(level1);
    game_engine->SetCurrentLevel(level1);
    game_engine->Run();
    
    delete game_engine;
    return 0;
}
