#include <iostream>
#include <random>
#include <climits>
#include "world.h"
using namespace world;

const bool logging = true;
const bool returnOnlyRectangles = true;
const int chunk_radius = 10000;
const int spacing = 2; // Default 1
const int min_size = 8;

int main()
{
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
    World world = World(seed, chunk_radius, min_size, spacing, logging, returnOnlyRectangles);
  }
  return 0;
}
