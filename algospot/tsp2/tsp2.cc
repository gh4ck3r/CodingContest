#include <iostream>
#include <algorithm>
#include <limits>

//#define NDEBUG
#include <cassert>

using namespace std;

using City = uint16_t;
using Cities = uint16_t;
using Distance = double;

const auto cMaxCities(sizeof(Cities) << 3);

Distance d[cMaxCities+1][cMaxCities];
Distance cache[cMaxCities+1][1<<cMaxCities];

Distance TSP(const City from, const Cities &cities)
{
  auto &_cache(cache[from][cities]);
  if (_cache) return _cache;
  if (!cities) return 0;

  Distance min_distance = numeric_limits<Distance>::infinity();
  for (auto k(0U); (1<<k) <= cities; ++k) {
    auto &&city(1<<k);
    if (!(cities & city)) continue;
    auto next_cities(cities);
    next_cities &= ~city;
    min_distance = min(min_distance, d[from][k] + TSP(k, next_cities));
  }

  return _cache = min_distance;
}

int main()
{
  cout.precision(10);
  cout.setf(ios::fixed);

  size_t C, N;
  cin >> C;
  while (C--) {
    fill(&d[0][0], &d[cMaxCities][cMaxCities], 0);
    fill(&cache[0][0], &cache[cMaxCities][1<<cMaxCities], 0);

    cin >> N;
    assert(N <= cMaxCities);
    for (auto from(0U); from < N; ++from) {
      for (auto to(0U); to < N; ++to) {
        cin >> d[from][to];
      }
    }

    cout << TSP(N, (1<<N)-1)<< endl;
  }
  return 0;
}
