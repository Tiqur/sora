#include <iostream>
#include <algorithm>
#include <optional>
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

namespace world
{
  class World
  {
    private:
      long seed;
      int spacing;
      int min_size;
      JavaRandom rand;
      bool isSlimeChunk(int x, int z);
      std::optional<std::vector<coords>> getCluster(int x, int z, int depth = 0);
      void search(int radius);

    public:
      void printMap(int radius);
      void printCluster(std::vector<coords> chunks);
      World(long seed, int radius, int min_size, int spacing) {
        this->min_size = min_size;
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
    for (int z = -half_radius; z < half_radius; z++)
      for (int x = -half_radius; x < half_radius; x++)
        getCluster(x, z, 1);
  }
  // Recursively search for nearby slime chunks within cluster and return dimensions
  std::optional<std::vector<coords>> World::getCluster(int x, int z, int depth)
  {
    // Holds coordinates of already checked chunks 
    static std::vector<coords> checked_chunks;
    coords current_coords = coords{x, z};
    
    // If not slime chunk and checked_chunks does not include these coordinates ( chunk hasn't been checked ), return false;
    bool contains_chunk = std::any_of(checked_chunks.begin(), checked_chunks.end(), [current_coords](coords c1){ return(c1.x == current_coords.x && c1.z == current_coords.z);});
    if (!this->isSlimeChunk(x, z) || contains_chunk) return {};

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

    // Return cluster if size >= min_size
    if (checked_chunks.size() >= this->min_size) {
        if (depth)
          std::cout << "size: " <<  checked_chunks.size() << " coords: " << x << " " << z << std::endl;
        return checked_chunks;
    }
    else return {};
  }

  // Display chunk cluster
  void World::printCluster(std::vector<coords> chunks)
  {
    // Initialize bounding box
    int top = chunks.front().x;
    int bottom = top;
    int left = chunks.front().z;
    int right = left;

    // Find bounding box
    for (coords &c : chunks) {
      if (c.z < left) left = c.z;
      if (c.z > right) right = c.z;
      if (c.x > top) top = c.x;
      if (c.x < bottom) top = c.x;
    }

    // Bounding box dimensions
    int width = right + 1 - left;
    int height = top + 1 - bottom;

    // Create 2D array representation of chunk cluster
    bool cluster[width][height] = {0};

    // Set cluster 
    for (int z = 0; z < width; z++)
    {
      for (int x = 0; x < height; x++)
      {
        coords c{x+bottom, z+left};
        bool chunks_contains = std::any_of(chunks.begin(), chunks.end(), [c](coords c1){ return(c1.x == c.x && c1.z == c.z);});
        cluster[z][x] = chunks_contains;
      }
    }

    // Display cluster
    for (int i = 0; i < width; i++) 
    {
      for (int j = 0; j < height; j++) 
      {
        std::cout << (cluster[i][j] ? "■ " : "□ ");
      }
      std::cout << std::endl;
    }
  }


  // Print map to console
  void World::printMap(int radius)
  {
    int half_radius = radius / 2;
    for (int z = -half_radius; z < half_radius; z+=this->spacing)
    {
      for (int x = -half_radius; x <= half_radius; x+=this->spacing)
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

