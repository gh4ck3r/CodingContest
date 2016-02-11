#include <iostream>
#include <algorithm>
#include <limits>
#include <cmath>
#include <numeric>
#include <cassert>
#include <cstring>

using namespace std;

const size_t maxN(100);
const size_t max_size_t(numeric_limits<size_t>::max());

size_t C, N, S;
int seq[maxN];
size_t cacheSSD[maxN][maxN];
size_t cacheQtz[maxN][maxN][maxN];

size_t ssd(const size_t &beg, const size_t &len)
{
  auto &cache(cacheSSD[beg][len]);
  if (cache  == max_size_t) {
    auto first(seq+beg);
    auto mean(round(accumulate(first, first + len, 0.) / len));

    cache = 0;
    for (size_t n(0); n < len; ++n) cache += pow(first[n] - mean, 2);
  }

  return cache;
}

size_t quantize(const size_t &beg = 0,
                const size_t &len = N,
                const size_t &qNum = S)
{
  if (!len) return 0;

  auto &cache(cacheQtz[beg][len][qNum]);
  if (cache == max_size_t) {
    if (qNum == 1 || seq[beg] == seq[beg+len-1]) cache = ssd(beg, len);
    else {
      cache = max_size_t;
      for (size_t i = 1; i < len; ++i) {
        auto *current(seq+beg+i);
        if (*(current-1) == *current) continue;
        cache = min(cache,
                     ssd(beg, i) + quantize(beg + i, len - i, qNum - 1));
      }
    }
  }
  return cache;
}

int main()
{
  cin >> C;
  while (C--) {
    cin >> N >> S;
    for (size_t i(0); i < N; ++i) cin >> seq[i];

    sort(seq, seq+N);

    memset(cacheSSD, -1, sizeof(cacheSSD));
    memset(cacheQtz, -1, sizeof(cacheQtz));

    cout << quantize() << endl;
  }
  return 0;
}
