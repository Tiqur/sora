#include <iostream>
#include "world.h"
using namespace world;

int main()
{
  int chunk_radius = 1000;
  int spacing = 1; // Default 1
  int min_size = 4;
  World world = World(-159660684484593011, chunk_radius, spacing);
  world.printMap(20);
  return 0;
}
