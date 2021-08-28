#include <iostream>
#include <vector>
#include "random.h"
using namespace javarand;


struct coords
{
  public:
    int x;
    int z;
};

struct cluster
{
  public:
    coords location;
    int width;
    int height;
};

namespace world
{
  class World
  {
    private:
      int seed;
      JavaRandom rand;
      cluster getCluster(int x, int z, int depth = 0);
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
      for (int z = -half_radius; z < half_radius; z++)
        getCluster(x, z, 1);
  }

  // Recursively search for nearby slime chunks within cluster and return dimensions
  cluster World::getCluster(int x, int z, int depth)
  {
    // If not slime chunk, return false;
    if (!this->isSlimeChunk(x, z)) return cluster{};

    // Holds coordinates of checked chunks ( initialized to 250 since it's virtually impossible for a cluster to be that size  )
    static std::vector<coords> checked_chunks;

    // If initial cluster check, clear checked_chunks
    if (depth)
      checked_chunks.clear();

    // Push self to checked chunks
    checked_chunks.push_back(coords{x, z});

    std::cout << checked_chunks.size() << std::endl;

    // Check sides
    //getCluster(x+1, z);
    //getCluster(x-1, z);
    //getCluster(x, z+1);
    //getCluster(x, z-1);

    // Check corners
    //getCluster(x-1, z+1);
    //getCluster(x+1, z-1);
    //getCluster(x+1, z+1);
    //getCluster(x-1, z-1);

  }

  // Print map to console
  void World::printMap(int radius)
  {
    int half_radius = radius / 2;
    for (int x = -half_radius; x < half_radius; x++)
    {
      for (int z = -half_radius; z < half_radius; z++)
        std::cout << (isSlimeChunk(x, z) ? "■ " : "□ ");
      std::cout << std::endl;
    }
  }

};

