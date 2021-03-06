#include <iostream>
#include <time.h>
#include <math.h>
#include "Engine.h"

using namespace std;

Engine* game_engine = new Engine("SpaceShooter", 60, 800, 640);
Level* level1 = new Level(5);
Sprite* player = AnimatedSprite::GetInstance("player", {"resources/game/player_space_ship1.png", "resources/game/player_space_ship2.png", "resources/game/player_space_ship3.png"}, 300, 300, 515, 128, 128);
Sprite* text_input = TextInputSprite::GetInstance("text_input", 400, 325);
Sprite* name_input_message = LabelSprite::GetInstance("name_message", "enter your name:", 208, 290);
Sprite* overlay = StaticSprite::GetInstance("overlay", "resources/game/transparent.png", 0, 0, 0, 0);

void GameOver(Sprite* sprite1, Sprite* sprite2) {
    overlay->SetIsVisible(true);
    Sprite* game_over_message = LabelSprite::GetInstance("game_over_message", "Game Over!", 280, 290);
    game_engine->GetCurrentLevel()->AddSprite(game_over_message);
    game_engine->GetCurrentLevel()->SetTimeListenersPaused(true);
    for (int i = 0; i < game_engine->GetCurrentLevel()->GetSprites().size(); i++) {
        if (game_engine->GetCurrentLevel()->GetSprites()[i]->GetTag() == "enemy") {
            game_engine->GetCurrentLevel()->RemoveSprite(game_engine->GetCurrentLevel()->GetSprites()[i]);
        }
    }
}

void DestroySprites(Sprite* sprite1, Sprite* sprite2) {
    game_engine->GetCurrentLevel()->RemoveSprite(sprite1);
    game_engine->GetCurrentLevel()->RemoveSprite(sprite2);
}

void CollisionListener(Sprite* sprite1, Sprite* sprite2) {
    if ((sprite1->GetTag() == "bullet" && sprite2->GetTag() == "enemy") || (sprite2->GetTag() == "bullet" && sprite1->GetTag() == "enemy")) {
        DestroySprites(sprite1, sprite2);
    } else if ((sprite1->GetTag() == "player" && sprite2->GetTag() == "enemy") || (sprite2->GetTag() == "player" && sprite1->GetTag() == "enemy")) {
        DestroySprites(sprite1, sprite2);
        GameOver(sprite1, sprite2);
    }
}

void PlayerRightMove(SDL_Event& event, Sprite* sprite) {
    sprite->SetX(sprite->GetX() + 20);
}

void PlayerLeftMove(SDL_Event& event, Sprite* sprite) {
    sprite->SetX(sprite->GetX() - 20);
}

void EnemyCreationListenerLevel1() {
    int x_pos = rand() % game_engine->GetWindowWidth() + 100;
    if (x_pos < (game_engine->GetWindowWidth() - 100)) {
        Sprite* tmpSprite = MovingSprite::GetInstance("enemy" ,"resources/game/level1_enemy.png", x_pos, 0, 100, 100, 0, 2);
        level1->AddSprite(tmpSprite);
    }
}

void BulletCreationListenerLevel1(SDL_Event& event, Sprite* sprite) {
    int x_pos = player->GetX()+54;
    Sprite* tmpSprite = MovingSprite::GetInstance("bullet", "resources/game/level1_bullet.png", x_pos, 505, 19, 43, 0, -10);
    level1->AddSprite(tmpSprite);
}

void PlayerNameEnteredListener() {
    overlay->SetIsVisible(false);
    level1->RemoveSprite(name_input_message);
    level1->RemoveSprite(text_input);
    player->AddEventListener(PlayerRightMove, SDLK_RIGHT);
    player->AddEventListener(PlayerLeftMove, SDLK_LEFT);
    level1->AddTimeListener(EnemyCreationListenerLevel1, 1000);
    player->AddEventListener(BulletCreationListenerLevel1, SDLK_SPACE);
    level1->AddSprite(player);
}

void SetUpLevel1() {
    level1->SetBackground("resources/game/level1_background.png");
    level1->AddSprite(overlay);
    level1->AddSprite(text_input);
    level1->AddSprite(name_input_message);
    game_engine->AddLevel(level1);
    game_engine->SetCurrentLevel(level1);
}

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    SetUpLevel1();
    game_engine->AddEventListener(PlayerNameEnteredListener, SDLK_RETURN);
    game_engine->SetCollisionListener(CollisionListener);

    game_engine->Run();
    
    delete game_engine;
    return 0;
}
