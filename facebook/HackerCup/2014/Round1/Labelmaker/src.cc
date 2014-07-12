#include <iostream>
#include <cassert>
#include <limits>
#include <algorithm>

#include "testcase.h"

//#define DEBUG

#define UNUSED(arg) (void)(arg)

class Labelmaker : public TestCase {
  public:
    using order_t = unsigned long long;
    bool parseInput(InputFetcher &input) override {
      input.fetch(mSeedStr, mOrder).nextline();
      assert(1<=mSeedStr.length()&&mSeedStr.length()<=25);
      assert(1<=mOrder&&mOrder<=std::numeric_limits<order_t>::max());
      return true;
    }

    void dump(std::ostream &os) const override {
      os << mSeedStr << " " << mOrder << std::endl;
    }

    bool run(unsigned int no=0) override {
      std::string output;
      auto l=mSeedStr.length();
      for(auto n=mOrder;n;n/=l)
        output += mSeedStr[--n%l];

      std::reverse(output.begin(), output.end());
      std::cout << "Case #" << no
                << ": " << output
                << std::endl;

      return true;
    }
  private:
    std::string mSeedStr;
    order_t     mOrder;
};

int main(int argc, char **argv)
{
  UNUSED(argc);UNUSED(argv);

  TestCaseContainer<Labelmaker> labelmakers;
  labelmakers.parseInput(std::cin);
  assert(1<=labelmakers.size()&&labelmakers.size()<=20);

  size_t i=0;
  for(auto lm:labelmakers) {
    ++i;
#ifdef DEBUG
    lm.dump(std::clog);
#endif
    lm.run(i);
  }

  return 0;
}
