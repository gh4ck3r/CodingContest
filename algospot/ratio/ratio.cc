#include <iostream>
#include <cmath>

using namespace std;

int main()
{
  size_t T, N, M, Z;
  cin >> T;
  while (T--) {
    cin >> N >> M;

    Z = 100 * M / N;

    cout << static_cast<int>(99 <= Z ?
              -1 :
              ceil( (static_cast<double>(Z + 1) * N - 100 * M) / (99 - Z) )
            )
         << endl;
  }
  return 0;
}
