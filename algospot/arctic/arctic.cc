#include <iostream>
#include <utility>
#include <set>
#include <limits>
#include <cmath>
#include <iomanip>

using namespace std;

using Base = pair<float, float>;
using Bases = set<Base>;

const float infinite = numeric_limits<float>::max();

istream &operator>>(istream &is, Bases &bs)
{
  Base b;
  is >> b.first >> b.second;
  bs.insert(b);
  return is;
}

float distanceBetween(const Base &a, const Base &b)
{
  return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

float minRadioPower(Bases &bases)
{
  Bases connected(bases.begin(), next(bases.begin()));
  bases.erase(bases.begin());

  float requiredPower = 0.;
  while (!bases.empty()) {
    Base baseToConnect;
    float distance = infinite;
    for (const auto &from : connected) {
      for (const auto &to : bases) {
        auto dist(distanceBetween(from, to));
        if (dist < distance) {
          distance = dist;
          baseToConnect = to;
        }
      }
    }
    bases.erase(baseToConnect);
    connected.insert(baseToConnect);
    requiredPower = max(requiredPower, distance);
  }

  return requiredPower;
}

int main()
{
  size_t C, N;
  cin >> C;
  while (C--) {
    Bases bases;

    cin >> N;
    while (N--) cin >> bases;

    cout << fixed << setprecision(2)
         << minRadioPower(bases)
         << endl;
  }
  return 0;
}
