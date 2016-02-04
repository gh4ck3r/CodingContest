#include <iostream>
#include <array>
#include <vector>

using namespace std;

using Cell = int;
using GridColumn = array<Cell, 4>;

array<GridColumn, 5> ValidColumns {
  GridColumn
  {0, 0, 0, 0},
  {1, 1, 0, 0},
  {1, 0, 0, 1},
  {0, 0, 1, 1},
  {1, 1, 1, 1}
};
GridColumn invalid1{0, 1, 1, 0};

int nWaysToTile(int width, GridColumn first_col = ValidColumns[0])
{
  switch (width) {
    case 0: return 0;
    case 1:
      for (const auto &valid : ValidColumns) {
        if (first_col == valid) return 1;
      }
      return 0;
  }

  int cnt = 0;
  if (first_col == ValidColumns[0]) {
    cnt += nWaysToTile(width-1, ValidColumns[0]);
    cnt += nWaysToTile(width-1, ValidColumns[1]);
    cnt += nWaysToTile(width-1, ValidColumns[2]);
    cnt += nWaysToTile(width-1, ValidColumns[3]);
    cnt += nWaysToTile(width-1, ValidColumns[4]);
  } else if (first_col == ValidColumns[1]) {
    cnt += nWaysToTile(width-1, ValidColumns[0]);
    cnt += nWaysToTile(width-1, ValidColumns[3]);
  } else if (first_col == ValidColumns[2]) {
    cnt += nWaysToTile(width-1, ValidColumns[0]);
    cnt += nWaysToTile(width-1, invalid1);
  } else if (first_col == ValidColumns[3]) {
    cnt += nWaysToTile(width-1, ValidColumns[0]);
    cnt += nWaysToTile(width-1, ValidColumns[1]);
  } else if (first_col == ValidColumns[4]) {
    cnt += nWaysToTile(width-1, ValidColumns[0]);
  } else if (first_col == invalid1) {
    cnt += nWaysToTile(width-1, ValidColumns[2]);
  }

  return cnt;
}

int main()
{
  int N, n = 0, W;
  cin >> N;
  while (N--) {
    cin >> W;
    cout << ++n << ' ' << nWaysToTile(W) << endl;
  }
  return 0;
}
