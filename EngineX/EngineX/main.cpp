#include <iostream>
#include "Engine.h"

int main(int argc, const char * argv[]) {
    Engine* game_engine = new Engine("My Game");
    Sprite* sprite = new ImageSprite("/Users/Peter/Desktop/include.png", 30, 30, 80, 163);
    game_engine->AddSprite(sprite);
    game_engine->Run();
    delete game_engine;
    return 0;
}
