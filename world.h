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

  bool World::isSlimeChunk(int x, int z) {
    std::cout << x << " " << z << std::endl;
    // Set seed and location
    rand.setSeed(
      this->seed +
      (int) (x * x * 0x4c1906) +
      (int) (x * 0x5ac0db) +
      (int) (z * z) * 0x4307a7L +
      (int) (z * 0x5f24f) ^ 0x3ad8025fL);

    // Determine if slime chunk
    return !(rand.nextInt(10));
  }

};

