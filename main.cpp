#include <iostream>
#include <random>
#include <climits>
#include "world.h"
using namespace world;

const bool logging = true;
const bool returnOnlyRectangles = true;
const int chunk_radius = 10000;
const int spacing = 4; 
const int min_size = 18;

int main()
{
  std::cout << "Starting Slime Chunk Finder..." << std::endl;
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "Logging: " << (logging ? "true" : "false") << std::endl;
  std::cout << "Return Only Rectangles: " << (returnOnlyRectangles ? "true" : "false") << std::endl; 
  std::cout << "Search Radius: " << chunk_radius << std::endl;
  std::cout << "Spacing Optimization: " << spacing << " ( +" << spacing-1 << "00% )" << std::endl;
  std::cout << "Minimum Cluster Size: " << min_size << std::endl;
  std::cout << "-----------------------------------------------" << std::endl;
  
  // Generate random number
  std::random_device rd;
  std::mt19937_64 eng(rd());
  std::uniform_int_distribution<long> distr;
  std::srand(time(NULL));

  // Main loop
  while (1)
  {
    // Generate seed
    long seed = distr(eng) * (rand() % 2 ? 1 : -1);

    // Search world
    std::cout << "Searching: " << seed << std::endl;
    World world = World(seed, chunk_radius, min_size, spacing, logging, returnOnlyRectangles);
  }
  return 0;
}
