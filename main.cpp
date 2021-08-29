#include <iostream>
#include "world.h"
using namespace world;

int main()
{
  int chunk_radius = 5000;
  int spacing = 2; // Default 1
  int min_size = 10;
  World world = World(-159660684484593011, chunk_radius, min_size, spacing);
  //world.printMap(20);
  return 0;
}
