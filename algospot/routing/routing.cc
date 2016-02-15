#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <algorithm>

#define DEBUG_HELPER
using namespace std;

using Noise = float;
using Computer = size_t;
using NoiseInfo = map<Computer, Noise>;
using NoiseMap = map<Computer, NoiseInfo>;

#ifdef DEBUG_HELPER
ostream& operator<<(ostream& os, const NoiseInfo &info)
{
  for (const auto &i : info) os << i.first << ": " << i.second << ' ';
  return os;
}

ostream& operator<<(ostream& os, const NoiseMap &noiseMap)
{
  for (const auto &fromInfo : noiseMap) {
    const auto &from(fromInfo.first);
    for (const auto &toInfo: fromInfo.second) {
      const auto &to(toInfo.first);
      const auto &noise(toInfo.second);
       os << '[' << from << ',' << to << "=" << noise << "] ";
    }
    os << endl;
  }
  return os;
}
#endif
Noise minNoisePath(const NoiseMap &noiseMap)
{
  size_t nComputers(noiseMap.size());
  Computer begin(0), end(nComputers-1);

  set<Computer> computers{0};
  while (computers.size() < nComputers) computers.insert(*computers.rbegin()+1);

  NoiseInfo noiseTo;
  noiseTo[begin] = 0;
  auto popClosestComputer = [&computers, &noiseTo] () {
    auto i(min_element(computers.begin(), computers.end(),
          [&noiseTo] (const Computer &a, const Computer &b) {
            return noiseTo[a] < noiseTo[b];
          }));
    auto c(*i);
    computers.erase(i);
    return c;
  };
  while (!computers.empty()) {
    auto nearestComputer(popClosestComputer());
    // XXX
  }
}

int main()
{
  size_t C;
  cin >> C;
  while (C--) {
    size_t N, M;
    cin >> N >> M;

    NoiseMap noiseMap;
    while (M--) {
      Noise n;
      Computer c1, c2;
      cin >> c1 >> c2 >> n;

      auto &prevNoise(noiseMap[c1][c2]);
      if (!prevNoise || prevNoise > n) {
        noiseMap[c2][c1] = prevNoise = n;
      }
    }

    clog << noiseMap << endl;

    cout << fixed << setprecision(8)
         << minNoisePath(noiseMap) << endl;

  }
  return 0;
}
