#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

using Node = size_t;
using NoiseRatio = double;

const Node MaxNode = 10000;
const NoiseRatio MaxNoiseRatio = numeric_limits<NoiseRatio>::max();

size_t C, N, M;
NoiseRatio noiseBetween[MaxNode][MaxNode];

NoiseRatio minNoiseRatio()
{
  const Node src(0), dst(N-1);

  NoiseRatio noiseTo[N];
  bool networkIncludes[N];

  for (auto n(src); n < N; ++n) {
    noiseTo[n] = MaxNoiseRatio;
    networkIncludes[n] = false;
  }

  noiseTo[src] = 1;
  for (size_t cnt(src); cnt < N; ++cnt) {
    Node shortestNode;
    NoiseRatio minNoise = MaxNoiseRatio;
    for (Node n(src); n < N; ++n) {
      if (networkIncludes[n]) continue;
      const auto &noise(noiseTo[n]);
      if (minNoise > noise) {
        minNoise = noise;
        shortestNode = n;
      }
    }
    networkIncludes[shortestNode] = true;

    for (Node n(src); n < N; ++n) {
      if (noiseBetween[shortestNode][n] == MaxNoiseRatio) continue;
      if (noiseTo[n] > noiseTo[shortestNode] * noiseBetween[shortestNode][n]) {
        noiseTo[n] = noiseTo[shortestNode] * noiseBetween[shortestNode][n];
      }
    }
  }

  return noiseTo[dst];
}

int main()
{
  cout << fixed << setprecision(10);
  cin >> C;
  while (C--) {
    cin >> N >> M;

    fill(&noiseBetween[0][0], &noiseBetween[N-1][N], MaxNoiseRatio);
    for (size_t  m(0); m < M; ++m) {
      size_t a, b;
      NoiseRatio c;
      cin >> a >> b >> c;

      auto &knownNoise(noiseBetween[a][b]);
      if (knownNoise > c) {
        knownNoise = noiseBetween[b][a] = c;
      }
    }

    cout << minNoiseRatio() << endl;
  }
  return 0;
}
