#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <numeric>
#include <iterator>
#include <cassert>

using namespace std;
using Sequence = vector<int>;

const size_t max_size_t = numeric_limits<size_t>::max();

size_t sumSquaredDiff(const Sequence::iterator &beg,
                      const Sequence::iterator &end)
{
  auto mean(round(accumulate(beg, end, 0.) / distance(beg, end)));

  auto sum(0);
  for (auto n = beg; n != end; ++n) sum += pow(*n - mean, 2);

  return sum;
}

size_t quantize(const Sequence::iterator &beg,
                const Sequence::iterator &end,
                const size_t &qNum)
{
  if (beg == end) return 0;

  switch (qNum) {
    case 0: assert(false);return max_size_t;  // Shold not be reached
    case 1: return sumSquaredDiff(beg, end);
  }

  auto minSum(max_size_t);
  auto sep(beg);
  for (++sep; sep != end; ++sep) {
    if (*sep == *prev(sep)) continue;

    minSum = min(minSum,
                 sumSquaredDiff(beg, sep) + quantize(sep, end, qNum - 1));
  }
  return minSum;
}

int main()
{
  size_t C, N, S;
  cin >> C;
  while (C--) {
    cin >> N >> S;
    Sequence seq(N);
    for (auto &n : seq) cin >> n;

    const auto &beg(seq.begin()), &end(seq.end());
    sort(beg, end);

    cout << quantize(beg, end, S) << endl;
  }
  return 0;
}
