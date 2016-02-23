#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

using City = int;
using Distance = double;

int main()
{
  cout.precision(10);
  cout.setf(ios::fixed);

  const size_t cMaxCities(10);
  size_t C, N;
  cin >> C;
  while(C--) {
    cin >> N;
    assert(N <= cMaxCities);

    Distance distances[cMaxCities][cMaxCities];
    for (size_t from(0);from < N; ++from) {
      for (size_t to(0);to < N; ++to) {
        cin >> distances[from][to];
      }
    }

    vector<City>  cities(N);
    iota(cities.begin(), cities.end(), 0);

    Distance min_dist(numeric_limits<Distance>::infinity());
    do {
      Distance dist_sum(0);
      for (auto now(cities.begin()), prev(now++);
           now != cities.end();
           ++now, ++prev) {
        dist_sum += distances[*prev][*now];
      }
      min_dist = min(min_dist, dist_sum);
    } while(next_permutation(cities.begin(), cities.end()));

    cout << min_dist << endl;
  }
  return 0;
}
