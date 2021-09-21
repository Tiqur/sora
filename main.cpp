#include <iostream>
#include <random>
#include <vector>
#include <climits>
#include "world.h"
using namespace world;

const bool logging = true;
const bool returnOnlyRectangles = true;
const int chunk_radius = 250;
const int spacing = 4; 
const int min_size = 16;

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
  std::uniform_int_distribution<long long unsigned> distr(0, 0xFFFFFFFFFFFFFFFF);
  std::srand(time(NULL));

  // Initialize cache array
  const int array_size = (chunk_radius / spacing + 1) * (chunk_radius / spacing + 1);
  long cached_coordinate_values[array_size];

  // Load cached_coordinate_values 
  int index = 0;
  int half_radius = chunk_radius / 2;
  for (int z = -half_radius; z < half_radius; z+= spacing)
    for (int x = -half_radius; x < half_radius; x+= spacing)
      cached_coordinate_values[index++] = getCoordinateValue(x, z);

  // Main loop
  while (true)
  {
    // Generate seed
    long long int seed = distr(eng) - 0x8000000000000000;

    // Search world
    std::cout << "Searching: " << seed << std::endl;
    World world = World(seed, chunk_radius, min_size, spacing, logging, returnOnlyRectangles, cached_coordinate_values, array_size, false);
  }

  return 0;
}
