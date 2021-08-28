#include <iostream>
#include "world.h"
using namespace world;

int main()
{
  World world = World(0);
  std::cout << world.isSlimeChunk(38, 11) << std::endl;
  return 0;
}
