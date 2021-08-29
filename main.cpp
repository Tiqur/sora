#include <iostream>
#include "world.h"
using namespace world;

int main()
{
  int chunk_radius = 10000;
  int spacing = 3; // Default 1
  int min_size = 14;
  World world = World(11, chunk_radius, min_size, spacing);
  //world.printMap(20);
  return 0;
}
