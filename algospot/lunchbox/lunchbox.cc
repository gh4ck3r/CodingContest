#include <iostream>
#include <vector>

using namespace std;

int main()
{
  size_t T, N;
  cin >> T;
  while (T--) {
    cin >> N;

    vector<int> M(N), E(N);
    for (auto &m : M) cin >> m;
    for (auto &e : E) cin >> e;
  }
  return 0;
}
