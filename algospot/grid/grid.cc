#include <iostream>

using namespace std;

int nWaysToTile(int width)
{
  // TODO : Implement
  return 0;
}

int main()
{
  int N, n = 0, W;
  cin >> N;
  while (N--) {
    cin >> W;
    cout << ++n << nWaysToTile(W) << endl;
  }
  return 0;
}
