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
      bool isSlimeChunk(int x, int z);
      void search(int radius);

    public:
      void printMap(int radius);
      World(long seed, int radius) {
        this->seed = seed;
        this->search(radius);
      }
  };

  // Determine if there is a slime chunk at x, z
  bool World::isSlimeChunk(int x, int z) 
  {
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

  // Search radius around 0, 0 for slime chunks
  void World::search(int radius)
  {
    int half_radius = radius / 2;
    for (int x = -half_radius; x < half_radius; x++)
    {
      for (int z = -half_radius; z < half_radius; z++)
      {
        // If slime chunk, find cluster size
        if (isSlimeChunk(x, z)) {

        }
      }
    }
  }

  void World::printMap(int radius)
  {
    int half_radius = radius / 2;
    for (int x = -half_radius; x < half_radius; x++)
      for (int z = -half_radius; z < half_radius; z++)
        std::cout << (isSlimeChunk(x, z) ? "■ " : "□ ");
      std::cout << std::endl;
  }

};

