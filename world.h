#include <iostream>
#include "random.h"
using namespace javarand;

namespace world
{
  class World
  {
    public:
      void test();
  };

  void World::test() {
    JavaRandom rand;
    rand.setSeed(0);
    std::cout << rand.nextInt() << std::endl;
  };
};

