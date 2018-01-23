#include "../headers/gameEngine.h"

/* g++ -std=c++11 *.cpp -o a.out -Wall -lncurses -lSDL2 -lSDL2_mixer -lpthread */

int main()
{
    auto engine = std::make_unique<gameEngine>();

    engine->run();

    return 0;
}
