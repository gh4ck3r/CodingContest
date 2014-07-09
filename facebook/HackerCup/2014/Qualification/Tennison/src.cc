#include <iostream>
#include <map>
#include <tuple>
#include <cassert>

#include "testcase.h"

#define UNUSED(arg) (void)(arg)

//#define DEBUG

class Tennison : public TestCase {
  public:
    bool parseInput(InputFetcher &input) override {
      UNUSED(input);

      input.fetch(K, Ps, Pr, Pi, Pu, Pw, Pd, Pl).nextline();
      assert(1<=K&&K<=100);
      assert(0<=Ps&&Ps<=1);
      assert(0<=Pr&&Pr<=1);
      assert(0<=Pi&&Pi<=1);
      assert(0<=Pu&&Pu<=1);
      assert(0<=Pw&&Pw<=1);
      assert(0<=Pd&&Pd<=1);
      assert(0<=Pl&&Pl<=1);

      return true;
    }

    void dump(std::ostream &os = std::clog) const override {
      UNUSED(os);
      os << K << ", "
         << Ps << ", "
         << Pr << ", "
         << Pi << ", "
         << Pu << ", "
         << Pw << ", "
         << Pd << ", "
         << Pl
         << std::endl;
    }

    double calcP(double p, size_t win=0, size_t lose=0)
    {
#ifdef DEBUG
      static int i=0;
      std::clog << i++ << ":calcP("<<win<<", "<<lose<<", "<<p<<")" <<std::endl;;
#endif
      if(win==0&&lose==0) mMemoize.clear();
      if(win == K){
#ifdef DEBUG
        std::clog << " - - 1.0" << std::endl;
#endif
        return 1.0;
      } else if(lose == K){
#ifdef DEBUG
        std::clog << " - - 0.0" << std::endl;
#endif
        return 0.0;
      }// else if(p<0.0000001) return 0.0;

      auto memoKey = std::make_tuple(win, lose, p);
      if(mMemoize.find(memoKey) != mMemoize.cend()) return mMemoize[memoKey];

      double PU=p+Pu; if(PU>1)PU=1;
      double PD=p-Pd; if(PD<0)PD=0;

      double result =    p  *    Ps  *    Pw  * calcP(PU, win+1, lose)
                    +    p  *    Ps  * (1-Pw) * calcP(p,  win+1, lose)
                    +    p  * (1-Ps) *    Pl  * calcP(PD, win, lose+1)
                    +    p  * (1-Ps) * (1-Pl) * calcP(p,  win, lose+1)
                    + (1-p) *    Pr  *    Pw  * calcP(PU, win+1, lose)
                    + (1-p) *    Pr  * (1-Pw) * calcP(p,  win+1, lose)
                    + (1-p) * (1-Pr) *    Pl  * calcP(PD, win, lose+1)
                    + (1-p) * (1-Pr) * (1-Pl) * calcP(p,  win, lose+1);

#ifdef DEBUG
      std::clog << " -- " << result << std::endl;
#endif
      mMemoize[memoKey] = result;
      return result;
    }

    bool run(unsigned int no=0) override {
      UNUSED(no);

      std::cout.precision(6);
      std::cout << "Case #" << no
                << ": " << std::fixed << calcP(Pi)
                << std::endl;
      return true;
    }
  private:
    size_t K;
    double Ps, Pr, Pi, Pu, Pw, Pd, Pl;
    std::map<std::tuple<size_t, size_t, double>,double> mMemoize;
};

int main(int argc, char **argv)
{
  UNUSED(argc);UNUSED(argv);

  TestCaseContainer<Tennison> games;

  games.parseInput(std::cin);
  assert(1<=games.size()&&games.size()<=100);

  size_t i=0;
  for(auto g:games) {
    ++i;
#ifdef DEBUG
    std::clog << "Case #" << i << std::endl;
    g.dump();
#endif
    g.run(i);
  }

  return 0;
}
