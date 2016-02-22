#include <iostream>
#include <vector>
#include <set>
#include <limits>

using namespace std;

using Distance = double;
using Distances = vector<vector<Distance>>;
Distances distances;

using City=int;
using Cities=set<City>;
Cities cities;
const City anywhere = -1;

Distance distance(const City &from, const City &to)
{
  if (from == anywhere || to == anywhere) return 0;
  return distances[from][to];
}

Distance tsp(const City from = anywhere, const Cities togo = cities)
{
  if (togo.size() == 1) {
    return distance(from, *togo.begin());
  }

  Distance d = numeric_limits<Distance>::max();
  for (auto &c : togo) {
    Cities next_togo(togo);
    next_togo.erase(c);
    d = min(d, tsp(c, next_togo) + distance(from, c));
  }
  return d;
}

int main()
{
  size_t C, N;
  cin >> C;
  cout.precision(10);
  cout.setf(ios::fixed);
  while(C--) {
    cin >> N;

    distances.assign(N, vector<Distance>(N, 0));
    for(auto &from : distances) for(auto &to : from) cin >> to;
    cities.clear(); for(size_t i = 0; i < N; ++i) cities.insert(i);

    cout << tsp() << endl;
  }
  return 0;
}
