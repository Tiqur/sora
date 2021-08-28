#include <iostream>
#include "world.h"
using namespace world;

int main()
{
  World world = World(0, 20);
  world.printMap(20);
  return 0;
}
