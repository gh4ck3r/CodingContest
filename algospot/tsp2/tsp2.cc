#include <iostream>
#include <algorithm>
#include <set>
#include <limits>
#include <map>

//#define NDEBUG
#include <cassert>

using namespace std;

using City = int;
using Cities = set<City>;
using Distance = double;

const auto cMaxCities(15U);
Distance d[cMaxCities][cMaxCities];

ostream &operator<<(ostream &os, const Cities &args)
{
  os << '{';
  for (const auto &a : args) {
    os << a;
    if (a != *args.rbegin()) os << ' ';
  }
  return os << '}';
}

ostream &operator<<(ostream &os, const vector<Cities> &args)
{
  for (const auto &a : args) os << a << endl;
  return os;
}

ostream &operator<<(ostream &os, const vector<bool> &args)
{
  for (const auto &a : args) os << (a ? '1':'0');
  return os;
}

vector<Cities> getSubsets(const Cities S, const size_t n)
{
  vector<Cities> ret;
  vector<bool> idx(S.size());

  fill_n(idx.begin(), n, true);
  do {
    Cities cities;
    for (auto s(find_if(idx.begin(), idx.end(), [](const bool &b) { return b; }));
         idx.end() != s;
         s = find_if(next(s), idx.end(), [](const bool &b) { return b; })) {
      auto offset(distance(idx.begin(), s));
      cities.insert(*(next(S.begin(), offset)));
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

    vector<map<Cities, Distance>> TSP(N);
    for (auto from(0U);from < N; ++from) TSP[from][{}] = 0;
    for (auto n(1U); n <= N; ++n) {
      for (auto from(0U);from < N; ++from) {
        auto S1(S);
        S1.erase(from);
        for (auto S2 : getSubsets(S1, n)) {
          auto &min_tsp(TSP[from][S2]);
          min_tsp = numeric_limits<Distance>::max();
          for (const auto &k : S2) {
            auto S3(S2);
            S3.erase(k);
            min_tsp = min(min_tsp, d[from][k] + TSP[k][S3]);
          }
        }
      }
    }

    auto min_dist(numeric_limits<Distance>::infinity());
    for (const auto &k : S) {
      auto S1(S);
      S1.erase(k);
      min_dist = min(min_dist, TSP[k][S1]);
    }
    cout << min_dist << endl;
  }
  return 0;
}
