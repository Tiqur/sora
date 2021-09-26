#include <iostream>
#include <random>
#include <vector>
#include <climits>
#include <arrayfire.h>
#include "world.h"

const bool logging = true;
const bool returnOnlyRectangles = true;
const int radius = 25;
const int spacing = 4; 
const int min_size = 16;
const int batch_size = 10;
const int array_length = std::ceil((float)(radius * radius + (radius % spacing == 0 ? 0 : radius*2)) / spacing);

int main()
{
  std::cout << "Starting Slime Chunk Finder..." << std::endl;
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "Logging: " << (logging ? "true" : "false") << std::endl;
  std::cout << "Return Only Rectangles: " << (returnOnlyRectangles ? "true" : "false") << std::endl; 
  std::cout << "Search Radius: " << radius << std::endl;
  std::cout << "Spacing Optimization: " << spacing << " ( +" << spacing-1 << "00% )" << std::endl;
  std::cout << "Minimum Cluster Size: " << min_size << std::endl;
  std::cout << "-----------------------------------------------" << std::endl;
  
  // Initialize generator with different value each time
  af::setSeed(time(NULL));

  // Initialize chunk coordinate values
  int x_coords[array_length];
  int z_coords[array_length];

  // Generate and fill chunk cordinate values
  int index = 0;
  for (int x = -radius; x < radius; x+=spacing)
    for (int z = -radius; z < radius; z+=spacing)
    {
      x_coords[index] = x;
      z_coords[index] = z;
      index++;
    }

  // Coordinate chunk values
  af::array X = af::array(1, array_length, x_coords);
  af::array Z = af::array(1, array_length, z_coords);

  // Create matrix of random values ( seeds )
  af::array SEEDS = af::randu(batch_size, s64);
  af_print(SEEDS)
  af_print(X)
  af_print(Z)
}
