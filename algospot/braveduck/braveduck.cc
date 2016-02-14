#include <iostream>
#include <utility>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

using Stone = pair<int, int>;
using Stones = set<Stone>;

size_t T, J, N;
Stone start, goal;
Stones stones;

istream &operator>>(istream &is, Stone &s)
{
  return is >> s.first >> s.second;
}

istream &operator>>(istream &is, Stones &ss)
{
  Stone s;
  is >> s;
  ss.insert(s);
  return is;
}

size_t distance(const Stone &a, const Stone &b)
{
  return ceil(sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2)));
}

bool isPossibleToEscapeFrom(const Stone &current)
{
  if (current == goal) return true;
  if (distance(current, goal) <= J) return true;

  auto nextAvailableStone([&current] () {
    return find_if(stones.begin(), stones.end(),
                   [&current] (const Stone &s) {
      return distance(current, s) <= J;
    });
  });

  for (auto candidate(nextAvailableStone());
       candidate != stones.end();
       candidate = nextAvailableStone()) {
    auto next(*candidate);
    stones.erase(candidate);
    if (isPossibleToEscapeFrom(next)) return true;
  }

  return false;
}

int main()
{
  cin >> T;
  while (T--) {
    cin >> J >> start >> goal >> N;

    stones.clear();
    while (N--) cin >> stones;

    cout << (isPossibleToEscapeFrom(start) ? "YES" : "NO") << endl;
  }
  return 0;
}
