#include <iostream>
#include "Engine.h"

int main(int argc, const char * argv[]) {
    Engine* game_engine = new Engine("My Game");
    delete game_engine;
    return 0;
}
