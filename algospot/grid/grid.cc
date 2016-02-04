#include <iostream>

using namespace std;

int main()
{
  size_t buf[3][45] { {1, 1,},
                      {0, 1,},
                      {0, 1,} };
  auto &F(buf[0]), &G(buf[1]), &H(buf[2]);

  size_t N, i = 0, W, max_W=1;
  cin >> N;
  while (N--) {
    cin >> W;

    if (max_W < W) {
      for (size_t n=max_W+1; n <= W; ++n) {
        F[n] = G[n] = H[n] = F[n-1];
        F[n] += 2*G[n-1] + H[n-1] + F[n-2];
        G[n] += G[n-1];
        H[n] += H[n-2];
      }
    }

    cout << ++i << ' ' << F[W] << endl;
  }
  return 0;
}
