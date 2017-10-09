#include "main.h"

using namespace Motherload;
int main(int argc, char *argv[])
{
    Game::instance->init();
    return 0;
}

void initGame()
{
    std::cout << "Hello from initGame!" << std::endl;
}