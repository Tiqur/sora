#include <iostream>
#include <algorithm>
#include <set>
#include "random.h"
using namespace javarand;


struct coords
{
  int x;
  int z;
};

bool operator<(const coords& c1, const coords& c2)
{
  return c1.x < c2.x;
}

struct cluster
{
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
    // Holds coordinates of checked chunks ( initialized to 250 since it's virtually impossible for a cluster to be that size  )
    static std::set<coords> checked_chunks;

    // If not slime chunk and checked_chunks does not include these coordinates ( chunk hasn't been checked ), return false;
    bool contains_chunk = std::find_if(checked_chunks.begin(), checked_chunks.end(), [x, z](coords const & item){ return item.x == x && item.z == z; }) != checked_chunks.end();
    if (!this->isSlimeChunk(x, z) || contains_chunk) return cluster{};

    // If initial cluster check, clear checked_chunks
    if (depth)
      checked_chunks.clear();

    // Push self to checked chunks
    checked_chunks.insert({x, z});


    // Check sides
    getCluster(x+1, z);
    getCluster(x-1, z);
    getCluster(x, z+1);
    getCluster(x, z-1);

    std::cout << checked_chunks.size() << std::endl;
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

