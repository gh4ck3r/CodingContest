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

    template<typename T, typename... Args>
    InputFetcher& fetch(T &data, Args&... args) {
      return operator>>(data).fetch(args...);
    }

    template<typename T>
    InputFetcher& operator>>(T &rhs) {
      if(mAutoNextLine && base::eof()) nextline();
      return static_cast<InputFetcher&>(base::operator>>(rhs));
    }

    InputFetcher& operator>>(std::basic_string<char> &rhs) {
      if(mAutoNextLine && base::eof()) nextline();
      std::istream(rdbuf()) >> rhs;
      return *this;
    }

    InputFetcher& operator>>(char &rhs) {
      if(mAutoNextLine && base::eof()) nextline();
      std::istream(rdbuf()) >> rhs;
      return *this;
    }

    template<typename T>
    operator T () {
      T val;
      operator>>(val);
      return val;
    }

  private:
    // Fallback of variadic template method
    InputFetcher& fetch() {return *this;}

  private:
    std::istream& mInputStream;
    bool          mAutoNextLine;
};

#endif // __INPUTFETCHER_H__
