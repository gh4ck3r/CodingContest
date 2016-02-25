#include <iostream>
#include <algorithm>
#include <set>
#include <limits>

//#define NDEBUG
#include <cassert>

using namespace std;

using City = int;
using Cities = set<City>;
using Distance = double;

const auto cMaxCities(15U);
Distance d[cMaxCities][cMaxCities];

Distance TSP(const City from, const Cities &cities)
{
  if (cities.empty()) return 0;

  Distance min_distance = numeric_limits<Distance>::infinity();
  for (const auto &k : cities) {
    auto next_cities(cities);
    next_cities.erase(k);
    min_distance = min(min_distance, d[from][k] + TSP(k, next_cities));
  }

  return min_distance;
}

int main()
{
  cout.precision(10);
  cout.setf(ios::fixed);

  size_t C, N;
  cin >> C;
  while (C--) {
    fill(&d[0][0], &d[cMaxCities-1][cMaxCities], 0);

    cin >> N;
    assert(N <= cMaxCities);
    for (auto from(0U); from < N; ++from) {
      for (auto to(0U); to < N; ++to) {
        cin >> d[from][to];
      }
    }

    set<City> S;
    for (auto city(0U);city < N; ++city) S.insert(city);

    cout << TSP(N, S)<< endl; // All d[N][*] are 0
  }
  return 0;
}
