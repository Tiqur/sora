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
      long seed;
      int spacing;
      JavaRandom rand;
      bool isSlimeChunk(int x, int z);
      cluster getCluster(int x, int z, int depth = 0);
      void search(int radius);

    public:
      void printMap(int radius);
      World(long seed, int radius, int spacing) {
        this->spacing = spacing;
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
    // Holds coordinates of already checked chunks 
    static std::vector<coords> checked_chunks;
    coords current_coords = coords{x, z};
    
    // If not slime chunk and checked_chunks does not include these coordinates ( chunk hasn't been checked ), return false;
    bool contains_chunk = std::any_of(checked_chunks.begin(), checked_chunks.end(), [current_coords](coords c1){ return(c1.x == current_coords.x && c1.z == current_coords.z);});
    if (!this->isSlimeChunk(x, z) || contains_chunk) return cluster{};

    // If initial cluster check, clear checked_chunks
    if (depth)
      checked_chunks.clear();

    // Push self to checked chunks
    checked_chunks.push_back(current_coords);

    // Check sides
    getCluster(x+1, z);
    getCluster(x-1, z);
    getCluster(x, z+1);
    getCluster(x, z-1);

    if (depth)
      std::cout << "size: " <<  checked_chunks.size() << " coords: " << x << " " << z << std::endl;
  }

  // Print map to console
  void World::printMap(int radius)
  {
    int half_radius = radius / 2;
    for (int x = -half_radius; x < half_radius; x+=this->spacing)
    {
      for (int z = -half_radius; z <= half_radius; z+=this->spacing)
      {
         if (z == -half_radius) {
          // Print x coordinates
          std::cout << (x >= 0 ? " " : "") << x << " ";
        } else {
          // Display chunk type
          std::cout << (isSlimeChunk(x, z) ? "■ " : "□ ");
        }
      }
      std::cout << std::endl;
    }

    for (int z = -half_radius; z < half_radius; z++)
      std::cout << z << " ";

  }

};

