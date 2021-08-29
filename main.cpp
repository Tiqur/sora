#include <iostream>
#include "world.h"
using namespace world;

int main()
{
  int chunk_radius = 12;
  int spacing = 1; // Default 1
  World world = World(-159660684484593011, chunk_radius, spacing);
  world.printMap(12);
  return 0;
}
