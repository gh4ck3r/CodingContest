#include <iostream>
#include <functional>
#include <map>
#include <algorithm>
#include <limits>
#include <cstdlib>

using namespace std;

using Score = size_t;
using offset_t = size_t;
using Evaluator  = function<bool (const offset_t, const offset_t)>;
using Evaluators = map<Score, Evaluator>;

bool isRepeatingNDecimals(const string &seq,
                          const offset_t beg,
                          const offset_t end,
                          const size_t n)
{
  const auto till(end - beg);
  for (offset_t i(n); i < till; ++i) {
    if (seq[beg+i] != seq[beg+i%n]) return false;
  }
  return true;
}

int getCommonDifference(const string &seq,
                        const offset_t beg,
                        const offset_t end)
{
  auto i(beg+1);
  const int diff(seq[i] - seq[beg]);
  while (++i < end) {
    if (diff != seq[i] - seq[i-1]) return 0;
  }
  return diff;
}

bool isArithmeticProgression(const string &seq,
                             const offset_t beg,
                             const offset_t end,
                             const int diff = 0)
{
  auto commonDiff(getCommonDifference(seq, beg, end));
  if (!commonDiff) return false;
  return !diff || diff == commonDiff;
}

const offset_t cMinUnitLen(3), cMaxUnitLen(5);
const Score cMaxScore(numeric_limits<Score>::max());

int main()
{
  size_t C;
  cin >> C;
  while (C--) {
    string seq;
    cin >> seq;

    using placeholders::_1;
    using placeholders::_2;
    using first_arg_t  = Evaluator::first_argument_type;
    using second_arg_t = Evaluator::second_argument_type;
    Evaluators evaluators {
      {1,  bind(isRepeatingNDecimals,    seq, _1, _2, 1)},
      {2,  bind(isArithmeticProgression, seq, _1, _2, 1)},
      {2,  bind(isArithmeticProgression, seq, _1, _2, -1)},
      {4,  bind(isRepeatingNDecimals,    seq, _1, _2, 2)},
      {5,  bind(isArithmeticProgression, seq, _1, _2, 0)},
      {10, [](first_arg_t, second_arg_t) { return true; }}
    };

    vector<Score> levelOf(seq.length() + 1);
    levelOf[0] = 0;
    levelOf[1] = levelOf[2] = evaluators.rbegin()->first;

    for (offset_t end(3); end <= seq.length(); ++end) {
      levelOf[end] = cMaxScore;
      auto offsetBegin(min(cMaxUnitLen, end));
      for (const auto &evaluator: evaluators) {
        const auto &score(evaluator.first);
        const auto &eval(evaluator.second);
        for (auto offset(offsetBegin); cMinUnitLen <= offset; --offset) {
          auto &level(levelOf[end]);
          auto beg(end - offset);
          if (eval(beg, end)) {
            level = min(level, score + levelOf[beg]);
          }
        }
      }
    }
    cout << levelOf[seq.length()] << endl;
  }
  return 0;
}
