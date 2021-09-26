#include <iostream>
#include <random>
#include <vector>
#include <climits>
#include <arrayfire.h>
#include "world.h"

const bool logging = true;
const bool returnOnlyRectangles = true;
const int chunk_radius = 250;
const int spacing = 4; 
const int min_size = 16;
const int batch_size = 10;

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
  
  // Initialize generator with different value each time
  af::setSeed(time(NULL));

  // Create matrix of random values ( seeds )
  af::array SEEDS = af::randu(batch_size, s64);
  af_print(SEEDS)



  // Main loop
  //while (true)
  //{
  //  // Generate seed
  //  long long int seed = distr(eng) - 0x8000000000000000;

  //  // Search world
  //  world::World world = world::World(seed, chunk_radius, min_size, spacing, logging, returnOnlyRectangles, cached_coordinate_values, array_size, false);
  //}

  return 0;
}
