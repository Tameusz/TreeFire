#include "headers/SFMLHandling.h"

int main()
{
    SFMLHandling simulation;
    SFMLHandling::createArena();
    simulation.run();
    return 0;
}
