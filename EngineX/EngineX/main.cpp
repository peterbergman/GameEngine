#include <iostream>
#include "Engine.h"

using namespace enginex;

int main(int argc, const char * argv[]) {
    Engine* game_engine = new Engine("My Game");
    delete game_engine;
    return 0;
}
