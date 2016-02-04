#include <iostream>

using namespace std;

enum Shape {shape0, shape1, shape2};

size_t nWaysToTile(size_t width, Shape first_col = shape0)
{
  switch (width--) {
    case 0: if (first_col != shape0) return 0;
    case 1: return 1;
  }

  size_t cnt = nWaysToTile(width, shape0);
  switch (first_col) {
    case shape0:
      cnt += nWaysToTile(width, shape1) * 2
           + nWaysToTile(width, shape2)
           + nWaysToTile(width-1, shape0);
      break;
    case shape1:
      cnt += nWaysToTile(width, shape1);
      break;
    case shape2:
      cnt += nWaysToTile(width-1, shape2);
      break;
  }
  return cnt;
}

int main()
{
  size_t N, n = 0, W;
  cin >> N;
  while (N--) {
    cin >> W;
    cout << ++n << ' ' << nWaysToTile(W) << endl;
  }
  return 0;
}
