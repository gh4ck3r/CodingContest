#ifndef __INPUTFETCHER_H__
#define __INPUTFETCHER_H__
#include <string>
#include <sstream>
class InputFetcher : protected std::istringstream
{
  using base = std::istringstream;
  public:
    InputFetcher() = delete;
    explicit InputFetcher(std::istream &is)
      : mInputStream(is), mAutoNextLine(false) {nextline();}

    InputFetcher& nextline() {
      std::string linebuf;
      std::getline(mInputStream, linebuf);
      base::str(linebuf);
      base::seekg(0);
      return *this;
    }
    bool autoNextLine() const          { return mAutoNextLine; }
    void autoNextLine(const bool &val) { mAutoNextLine = val; }

    template<typename T>
    InputFetcher& operator>>(T &rhs) {
      if(mAutoNextLine && base::eof()) nextline();
      return static_cast<InputFetcher&>(base::operator>>(rhs));
    }
    template<typename T>
    operator T () {
      T val;
      operator>>(val);
      return val;
    }

  private:
    std::istream& mInputStream;
    bool          mAutoNextLine;
};

#endif // __INPUTFETCHER_H__
