#include <iostream>
#include <cassert>
#include <limits>
#include <algorithm>

#include "testcase.h"

//#define DEBUG

#define UNUSED(arg) (void)(arg)

class AAAAAA : public TestCase {
  public:
    using order_t = unsigned long long;
    bool parseInput(InputFetcher &input) override {
      input.fetch(mHeight, mWidth).nextline();
      assert(1<=mWidth&&mWidth<=500);
      assert(1<=mHeight&&mHeight<=500);

      for(size_t i=0;i<mHeight;++i) {
        std::string line;
        input.fetch(line).nextline();
        assert(line.length() == mWidth);
        mMatrix.push_back(line);
      }
      //mWidth--;mHeight--;
      return true;
    }

    void dump(std::ostream &os) const override {
      for(auto line:mMatrix) os << line << std::endl;
    }

    using direction_t = enum {Right, Down, Left, Up};
    size_t G(const size_t aX=0, const size_t aY=0, const direction_t aD=Left, const bool aUsed=false) {
#ifdef DEBUG
      std::clog << "x : " << aX << ", y : " << aY
                << ", d : " << (aD==Right?"Right":aD==Down?"Down":aD==Left?"Left":aD==Up?"Up":"Unknown")
                << ", Used : " << (aUsed?"true":"false") << std::endl;
#endif
      using cell_t = struct {
        size_t x;
        size_t y;
        direction_t d;
        bool u;
      };
      std::vector<cell_t> cells;
      std::vector<size_t> candidates;

      if(aD==Left && aUsed) {
        cells.push_back({aX  , aY+1, Down, aUsed});
        cells.push_back({aX-1, aY  , Left, aUsed});
      } else if(aD==Up && aUsed) {
        cells.push_back({aX+1, aY  , Right, aUsed});
        cells.push_back({aX  , aY-1, Up   , aUsed});
      } else {
        cells.push_back({aX+1, aY  , Right, aUsed});
        cells.push_back({aX  , aY+1, Down , aUsed});
        if(aD==Right && !aUsed)     cells.push_back({aX  , aY-1, Up   , true});
        else if(aD==Down && !aUsed) cells.push_back({aX-1, aY  , Left , true});
      }

      for(auto cell:cells){
        auto x=cell.x, y=cell.y;
        if(x < mWidth && y < mHeight && mMatrix[y][x]!='#')
          candidates.push_back(G(x, y, cell.d, cell.u));
      }

      size_t candidate_siz=candidates.size();
#ifdef DEBUG
      std::clog  << "candidates size : " << candidate_siz << std::endl;
#endif
      return 1+(!candidate_siz?0:
             candidate_siz==1?candidates.back():
             *std::max_element(candidates.begin(), candidates.end()));
    }
    bool run(unsigned int no=0) override {
      auto output = G();
      std::cout << "Case #" << no
                << ": " << output
                << std::endl;

      return true;
    }
  private:
    size_t mWidth=0, mHeight=0;
    std::vector<std::string> mMatrix;

};

int main(int argc, char **argv)
{
  UNUSED(argc);UNUSED(argv);

  TestCaseContainer<AAAAAA> aaaaaa;
  aaaaaa.parseInput(std::cin);
  assert(1<=aaaaaa.size()&&aaaaaa.size()<=20);

  size_t i=0;
  for(auto a:aaaaaa) {
    ++i;
#ifdef DEBUG
    a.dump(std::clog);
#endif
    a.run(i);
  }

  return 0;
}
