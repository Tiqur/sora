namespace javarand
{
  class JavaRandom
  {
    private:
      const long multiplier = 0x5DEECE66DL;
      const long addend = 0xBL;
      const long mask = (1L << 48) -1;

      long initialScramble(long seed);
      int next(int bits);

    public:
      long seed;
      void setSeed(long seed);
      int nextInt();
  };

  // Set the seed of this random number generator
  void JavaRandom::setSeed(long seed)
  {
    this->seed = this->initialScramble(seed);
  }

  // Scramble initial seed
  long JavaRandom::initialScramble(long seed)
  {
    return (seed ^ this->multiplier) & this->mask;
  }

  // Generates the next pseudorandom number
  int JavaRandom::next(int bits)
  {
    this->seed = (this->seed * this->multiplier + this->addend) & this->mask;
    return (unsigned int)(this->seed >> (48 - bits));
  }

  // Generate next pseudorandom int
  int JavaRandom::nextInt()
  {
    return this->next(32);
  }
};

