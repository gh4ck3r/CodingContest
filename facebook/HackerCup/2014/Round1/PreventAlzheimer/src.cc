#include <iostream>
#include <cassert>
#include <limits>
#include <algorithm>

#include "testcase.h"

//#define DEBUG

#define UNUSED(arg) (void)(arg)

class PreventAlzheimer : public TestCase {
  public:
    bool parseInput(InputFetcher &input) override {
      size_t n_grandchildren = 0;
      input.fetch(n_grandchildren, mK).nextline();
      assert(2<=n_grandchildren&&n_grandchildren<=20);
      assert(1<=mK&&mK<=20);
      while(n_grandchildren--) {
        size_t age(input);
        assert(age<=50);
        mGrandChildren.push_back(age);
      }
      input.nextline();
      return true;
    }

    void dump(std::ostream &os) const override {
      os << "K : " << mK << std::endl;
      for(auto c:mGrandChildren)
        os << c << " ";
      os << std::endl;
    }


    size_t gcd (size_t a, size_t  b)
    {
      size_t c;
      while ( a != 0 ) {
        c = a; a = b%a;  b = c;
      }
      return b;
    }

    size_t findX(std::vector<size_t>::iterator v) {
      for(size_t x=0;x<=50;++x) {
        if((*v+x) % mK == 0){
#ifdef DEBUG
          std::clog << "  trying : " << x << std::endl;
#endif
          bool found_other_gcd = false;
          for(auto c=mGrandChildren.begin();c!=v;++c){
            if(gcd(*v+x, *c)!=mK){
              found_other_gcd = true;
              break;
            }
          }
          if(!found_other_gcd) return x;
        }
      }
      assert(false);
      return 0;
    }

    size_t calcNewSumDiff() {
      std::vector<size_t> X;
      for(auto i=mGrandChildren.begin();i!=mGrandChildren.end();++i){
        size_t x = findX(i);
#ifdef DEBUG
        std::clog << "i : " << *i << ", x : " << x << std::endl;
#endif
        X.push_back(x);
        *i+=x;
      }

      size_t ret = 0;
      for(auto v:X) ret+=v;
#ifdef DEBUG
      std::cout << "sum : " << ret << std::endl;
#endif
      return ret;
    }

    bool run(unsigned int no=0) override {
#if 0
      size_t OldSum = 0;
      for(auto c:mGrandChildren) OldSum = c;
#endif
      std::sort(mGrandChildren.begin(), mGrandChildren.end());

      std::cout << "Case #" << no
        << ": " << calcNewSumDiff()
        << std::endl;

      return true;
    }
  private:
    size_t mK;
    std::vector<size_t> mGrandChildren;
};

int main(int argc, char **argv)
{
  UNUSED(argc);UNUSED(argv);

  TestCaseContainer<PreventAlzheimer> pas;
  pas.parseInput(std::cin);
  assert(1<=pas.size()&&pas.size()<=20);

  size_t i=0;
  for(auto pa:pas) {
    ++i;
#ifdef DEBUG
    pa.dump(std::clog);
#endif
    pa.run(i);
  }

  return 0;
}
