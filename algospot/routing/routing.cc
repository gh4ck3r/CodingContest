#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

using Noise = double;
using Computer = size_t;
using NoiseInfo = map<Computer, Noise>;
using NoiseMap = map<Computer, NoiseInfo>;

Noise minNoisePath(const NoiseMap &noiseMap)
{
  size_t nComputers(noiseMap.size());
  Computer begin(0), goal(nComputers-1);
  set<Computer> computers;
  while (nComputers--) computers.insert(nComputers);

  NoiseInfo noiseTo;
  noiseTo[begin] = 1;

  auto popClosestComputer = [&computers, &noiseTo] () {
    auto i(min_element(computers.begin(), computers.end(),
          [&noiseTo] (const Computer &a, const Computer &b) {
            return noiseTo[a] && noiseTo[a] < noiseTo[b];
          }));
    auto c(*i);
    computers.erase(i);
    return c;
  };

  while (!computers.empty()) {
    const auto nearestComputer(popClosestComputer());
    for (const auto &c : noiseMap.at(nearestComputer)) {
      const auto &neighbor(c.first);
      const auto &noise(noiseTo[nearestComputer] * c.second);

      if (!noiseTo[neighbor] || noiseTo[neighbor] > noise) {
        noiseTo[neighbor] = noise;
      }
    }
  }

  return noiseTo[goal];
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

    cout << fixed << setprecision(10)
         << minNoisePath(noiseMap) << endl;

  }
  return 0;
}
