#include <iostream>
#include "world.h"
using namespace world;

int main()
{
  World world = World(0, 50);
  world.printMap(50);
  return 0;
}
