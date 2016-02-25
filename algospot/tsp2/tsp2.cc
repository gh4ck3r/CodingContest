#include <iostream>
#include <algorithm>
#include <set>
#include <limits>
#include <map>
#include <functional>

//#define NDEBUG
#include <cassert>

using namespace std;

using City = int;
using Cities = set<City>;
using Distance = double;
using TSP = vector<map<Cities, Distance>>;

const auto cMaxCities(15U);
Distance d[cMaxCities][cMaxCities];

set<City> operator-(const set<City> &S, const City &c)
{
  set<City> newS(S);
  newS.erase(c);
  return newS;
}

vector<Cities> getSubsets(const Cities &S, const size_t n)
{
  vector<Cities> ret;
  vector<bool> idx(S.size());

  fill_n(idx.begin(), n, true);
  auto find_true([&idx](vector<bool>::iterator begin) {
      return find_if(begin, idx.end(), [](const bool &b) { return b; });
    });
  do {
    Cities cities;
    for (auto &&s(find_true(idx.begin()));
         idx.end() != s;
         s = find_true(next(s))) {
      cities.insert(*(next(S.begin(), distance(idx.begin(), s))));
    }
    ret.push_back(cities);
  } while (prev_permutation(idx.begin(), idx.end()));

  return ret;
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

    TSP tsp(N);
    auto min_tsp(numeric_limits<Distance>::infinity());
    for (auto n(1U); n < N; ++n) {
      for (const auto &from : S) {
        auto &&S1(S-from);
        for (const auto &S2 : getSubsets(S1, n)) {
          const auto cal_tsp([&](const City &k) {
              return d[from][k] + tsp[k][S2-k];
            });
          const auto k(*min_element(S2.begin(), S2.end(),
                [&](const City &k1, const City &k2) {
                  return cal_tsp(k1) < cal_tsp(k2);
                }));

          tsp[from][S2] = cal_tsp(k);
        }
        if (n == N-1) min_tsp = min(min_tsp, tsp[from][S1]);
      }
    }

    cout << min_tsp << endl;
  }
  return 0;
}
