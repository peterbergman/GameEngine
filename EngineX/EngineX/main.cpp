#include <iostream>
#include "Engine.h"

using namespace std;

void Print(ActionEvent event) {
    cout << "clicked!\n";
}

int main(int argc, const char * argv[]) {
    
    Engine* game_engine = new Engine("My Game");
    Sprite* sprite = new ImageSprite("/Users/Peter/Desktop/include.png", 30, 30, 80, 163);
    sprite->AddActionListener(Print);
    game_engine->AddSprite(sprite);
    game_engine->Run();
    delete game_engine;
    return 0;
}
