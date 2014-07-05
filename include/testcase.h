#ifndef __TESTCASE_H__
#define __TESTCASE_H__

#include <iostream>
#include <vector>

#include "inputfetcher.h"

class TestCase
{
  public:
    virtual bool parseInput(InputFetcher &input) = 0;
    virtual void dump(std::ostream &os) const = 0;
    virtual bool run(unsigned int no=0) = 0;
  protected:
    void printBoundary(std::ostream &os, const char marker) const {
      char oldfill = os.fill(marker);
      std::streamsize oldwidth(os.width(80));
      os << std::string() << std::endl;
      os.fill(oldfill);
      os.width(oldwidth);
    };

};

template <typename T>
class TestCaseContainer : protected std::vector<T>
{
  using base           = std::vector<T>;

  using iterator       = typename base::iterator;
  using const_iterator = typename base::const_iterator;
  using size_type      = typename base::size_type;

  public:
    iterator       begin()       noexcept { return base::begin(); }
    const_iterator begin() const noexcept { return base::begin(); }
    iterator       end()         noexcept { return base::end(); }
    const_iterator end()   const noexcept { return base::end(); }
    size_type      size()  const noexcept { return base::size(); }

    void addCase(const T &aNewCase) { base::push_back(aNewCase); }
    void addCase(T &&aNewCase) { base::push_back(aNewCase); }

    bool parseInput(std::istream &is) {
      InputFetcher input(is);

      int testcase_cnt(input);
      input.nextline();

      while(testcase_cnt--) {
        T newcase;
        if(!newcase.parseInput(input))
          return false;
        addCase(newcase);
      }

      return testcase_cnt==0;
    }
  protected:
  private:
};

#endif // __TESTCASE_H__
