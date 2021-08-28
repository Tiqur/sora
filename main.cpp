#include "random.h"
#include <iostream>

using namespace javarand;

int main()
{
  JavaRandom rand;
  rand.setSeed(0);
  std::cout << rand.nextInt() << std::endl;
  return 0;
}
