#include <iostream>
#include <list>
#include <algorithm>
#include <limits>
#include <cmath>
#include <numeric>

using namespace std;
using Sequence = list<int>;

size_t sumSquaredDiff(const Sequence &s)
{
  auto mean(round(accumulate(s.begin(), s.end(), 0.) / s.size()));

  auto sum(0);
  for (const auto &n : s) sum += pow(n - mean, 2);

  return sum;
}

size_t quantize(Sequence seq, size_t qNum)
{
  if (seq.empty()) return 0;

  size_t minSum(numeric_limits<size_t>::max());
  switch (qNum) {
    case 0: return minSum;
    case 1: return sumSquaredDiff(seq);
  }

  Sequence head;
  while (!seq.empty()) {
    head.push_back(seq.front());
    seq.pop_front();
    if (head.back() == seq.front()) continue;

    minSum = min(minSum, sumSquaredDiff(head) + quantize(seq, qNum - 1));
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
    seq.sort();

    cout << quantize(seq, S) << endl;
  }
  return 0;
}
