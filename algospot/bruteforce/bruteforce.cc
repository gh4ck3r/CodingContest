#include <iostream>

using namespace std;

const uint32_t cUpperBound = 1000000007;

inline bool isOdd(const uint32_t &n)
{
  return n & 1;
}

uint64_t pow(const uint32_t &base, const uint32_t &exp)
{
  switch (exp) {
    case 0: return 1;
    case 1: return base;
  }
  auto half(pow(base, exp>>1));
  half *= half;
  half %= cUpperBound;
  if (isOdd(exp)) half *= base;
  return half % cUpperBound;
}

uint64_t CntCmbUntil(const uint32_t &nUnit, const uint32_t &n)
{
  uint64_t ret(
      n <= 1   ? 1 :
      isOdd(n) ? CntCmbUntil(nUnit, n - 1) + pow(nUnit, n - 1) :
      /* Even */ CntCmbUntil(nUnit, n >> 1) * (1 + pow(nUnit, n >> 1)));
  return ret % cUpperBound;
}

uint64_t CountCombinationBetween(const uint32_t &minDigits,
                                 const uint32_t &maxDigits,
                                 const uint32_t &nUnit)
{
  auto ret(
      pow(nUnit, minDigits) * CntCmbUntil(nUnit,  maxDigits - minDigits + 1));
  return ret % cUpperBound;
}

int main()
{
  uint32_t C, A, B, N;
  cin >> C;
  while (C--) {
    cin >> A >> B >> N;
    cout << CountCombinationBetween(A, B, N) << endl;
  }
  return 0;
}
