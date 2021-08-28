namespace javarand
{
  class JavaRandom
  {
    private:
      const long multiplier = 0x5DEECE66DL;
      const long addend = 0xBL;
      const long mask = (1L << 48) -1;

      long initialScramble(long seed);
      void setSeed(long seed);
      int next(int bits);

    public:
      long seed;

  };

  void JavaRandom::setSeed(long seed)
  {
    this->seed = this->initialScramble(seed);
  }

  long JavaRandom::initialScramble(long seed)
  {
    return (this->seed ^ this->multiplier) & this->mask;
  }
};

