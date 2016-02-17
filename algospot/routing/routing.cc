#include <iostream>
#include <iomanip>
#include <utility>
#include <map>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>

using namespace std;

using Noise      = double;
using Computer   = size_t;
using NoiseInfo  = map<Computer, Noise>;
using NoiseMap   = vector<NoiseInfo>;

using NoiseInfoQEntry = pair<NoiseInfo::mapped_type, NoiseInfo::key_type>;
using NoiseInfoQ      = priority_queue<NoiseInfoQEntry,
                                       vector<NoiseInfoQEntry>,
                                       greater<NoiseInfoQEntry>>;

istream &operator>>(istream &is, NoiseMap &aNoiseMap)
{
  Noise c;
  Computer a, b;
  is >> a >> b >> c;

  aNoiseMap[a][b] = c;
  aNoiseMap[b][a] = c;

  return is;
}

Noise minNoiseRatio(const NoiseMap &aNoiseMap)
{
  const Computer src(0), dst(aNoiseMap.size() - 1);
  const Noise &infinite_noise(numeric_limits<Noise>::infinity());

  NoiseInfo cost_to;
  NoiseInfoQ nodes_to_enclose;

  nodes_to_enclose.push({cost_to[src] = 1, src});
  for (auto node(src+1); node <= dst; ++node) {
    nodes_to_enclose.push({cost_to[node] = infinite_noise, node});
  }

  while (!nodes_to_enclose.empty()) {
    const auto &shortest_node_info(nodes_to_enclose.top());
    const auto queued_cost(shortest_node_info.first);
    const auto shortest_node(shortest_node_info.second);
    nodes_to_enclose.pop();

    const auto cost_to_shortest = cost_to[shortest_node];
    if (queued_cost > cost_to_shortest) continue;

    for (const auto &adj_info : aNoiseMap[shortest_node]) {
      const auto &adj(adj_info.first);
      auto cost_to_adj(cost_to_shortest * adj_info.second);
      auto &known_cost_to_adj(cost_to[adj]);
      if (cost_to_adj < known_cost_to_adj) {
        known_cost_to_adj = cost_to_adj;
        nodes_to_enclose.push({cost_to_adj, adj});
      }
    }
  }

  return cost_to[dst];
}

int main()
{
  cout << fixed << setprecision(10);

  size_t C, N, M;
  cin >> C;
  while (C--) {
    cin >> N >> M;

    NoiseMap noise_map(N);
    while (M--) cin >> noise_map;

    cout << minNoiseRatio(noise_map) << endl;
  }

  return 0;
}
