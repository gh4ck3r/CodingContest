#include <iostream>
#include <cassert>

#include "testcase.h"

#define UNUSED(v) (void)(v)


class SquareDetector : public TestCase {
  const char white='.';
  const char black='#';
  using color_t      = char;
  using color_line_t = std::string;
  using color_rect_t = std::vector<color_line_t>;
  public:
    bool parseInput(InputFetcher &input) override {
      size_t n;

      input.fetch(n).nextline();
      for(size_t i=0;i<n;++i, input.nextline()) {
        color_line_t line;
        input >> line;
        mData.push_back(line);
      }

      return true;
    }

    void dump(std::ostream &os = std::clog) const override {
      for(auto i:mData) {
        for(auto j:i) {
          os << j;
        }
        os << std::endl;
      }
    }

    bool run(unsigned int no=0) override {
#ifdef DEBUG
      dump(std::cout);
#endif
      size_t size=0;
      std::pair<size_t, size_t> square_begin_point = {0,0};

      for(auto line:mData) {
        size_t end   = line.rfind(black);
        if(end == std::string::npos){
          ++square_begin_point.first;
          continue;
        }

        square_begin_point.second = line.find(black);
        size = end-square_begin_point.second+1;
        break;
      }

      bool square=true;
      for(size_t i=0;square&&i<mData.size();++i) {
        for(size_t j=0;square&&j<mData[i].length();++j) {
          if(square_begin_point.first <= i && i < square_begin_point.first+size
              && square_begin_point.second <= j && j < square_begin_point.second+size){
            if(mData[i][j]==white) square=false;
          } else {
            if(mData[i][j]==black) square=false;
          }
#ifdef DEBUG
          if(!square) {
            std::cout << "(" << square_begin_point.first << "," << square_begin_point.second << ":" << size << ")"<< std::endl;
            std::cout << "(" << i << "," << j << "-" << mData[i][j] << ")" << std::endl;
          }
#endif
        }
      }
      std::cout << "Case #" << no << ":" << (square?"YES":"NO") << std::endl;
      return true;
    };
  private:
    color_rect_t mData;
};

int main(int argc, char **argv)
{
  UNUSED(argc);UNUSED(argv);

  TestCaseContainer<SquareDetector> games;

  games.parseInput(std::cin);
  assert(1 <= games.size() && games.size() <=20);

  size_t i=0;
  for(auto g:games) {
    ++i;
#ifdef DEBUG
    std::clog << i << std::endl;
    g.dump();
#endif
    g.run(i);
  }

  return 0;
}

