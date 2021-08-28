#include <iostream>
#include "random.h"
using namespace javarand;

namespace world
{
  class World
  {
    private:
      int seed;
      JavaRandom rand;

    public:
      bool isSlimeChunk(int x, int z);
      World(long seed) {
        this->seed = seed;
      }
  };

};

