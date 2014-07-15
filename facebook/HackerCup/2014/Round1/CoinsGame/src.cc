#include <iostream>
#include <cassert>
#include <cmath>
#include <ctgmath>
#include <algorithm>

#include "testcase.h"

#define UNUSED(arg) (void)(arg)

//#define DEBUG

class CoinGame : public TestCase {
  public:
    bool parseInput(InputFetcher &input) override {
      input.fetch(mNumJar, mNumCoins, mExpectedCoins).nextline();
      assert(1<=mNumJar && mNumJar<=1000000);
      assert(1<=mExpectedCoins);
      assert(mExpectedCoins<=mNumCoins);
      assert(mNumCoins<=1000000);
      return true;
    }

    void dump(std::ostream &os=std::clog) const override {
      os << "N:" << mNumJar << ", "
         << "K:" << mNumCoins << ", "
         << "C:" << mExpectedCoins
         << std::endl;
    }

    bool run(unsigned int no) override {
      int x = ceil(static_cast<double>(mExpectedCoins)/mNumJar);
      std::cout << "#Case " << no << ":"
                << mExpectedCoins+mNumJar-std::min(mNumJar, mNumCoins/x)
                << std::endl;
      return true;
    }
  private:
    size_t mNumJar;
    size_t mNumCoins;
    size_t mExpectedCoins;
};

int main(int argc, char **argv)
{
  UNUSED(argc);UNUSED(argv);
  TestCaseContainer<CoinGame> games;
  games.parseInput(std::cin);
  assert(1<=games.size()&&games.size()<=20);

  size_t i=0;
  for(auto g:games) {
    ++i;
#ifdef DEBUG
    g.dump();
#endif
    g.run(i);
  }
  return 0;
}
