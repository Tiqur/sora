#include <iostream>
#include "world.h"
using namespace world;

int main()
{
  World world = World(1, 12);
  world.printMap(12);
  return 0;
}
