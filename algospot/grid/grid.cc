#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

using Cell = int;
using GridColumn = array<Cell, 4>;
using Grid = vector<GridColumn>;

array<GridColumn, 5> ValidColumns {
  GridColumn
  {0, 0, 0, 0},
  {1, 1, 0, 0},
  {1, 0, 0, 1},
  {0, 0, 1, 1},
  {1, 1, 1, 1}
};
GridColumn invalid1{0, 1, 1, 0};

int nWaysToTile(Grid grid)
{
  GridColumn &first_col(grid.front());
  switch (grid.size()) {
    case 0: return 0;
    case 1:
      for (const auto &valid : ValidColumns) {
        if (first_col == valid) return 1;
      }
      return 0;
  }

  int cnt = 0;
  if (first_col == ValidColumns[0]) {
    Grid next_grid(grid.begin()+1, grid.end());
    cnt += nWaysToTile(next_grid);

    next_grid.front() = ValidColumns[1];
    cnt += nWaysToTile(next_grid);

    next_grid.front() = ValidColumns[2];
    cnt += nWaysToTile(next_grid);

    next_grid.front() = ValidColumns[3];
    cnt += nWaysToTile(next_grid);

    next_grid.front() = ValidColumns[4];
    cnt += nWaysToTile(next_grid);
  } else if (first_col == ValidColumns[1]) {
    Grid next_grid(grid.begin()+1, grid.end());
    cnt += nWaysToTile(next_grid);

    next_grid.front() = ValidColumns[3];
    cnt += nWaysToTile(next_grid);
  } else if (first_col == ValidColumns[2]) {
    Grid next_grid(grid.begin()+1, grid.end());
    cnt += nWaysToTile(next_grid);

    next_grid.front() = invalid1;
    cnt += nWaysToTile(next_grid);
  } else if (first_col == ValidColumns[3]) {
    Grid next_grid(grid.begin()+1, grid.end());
    cnt += nWaysToTile(next_grid);

    next_grid.front() = ValidColumns[1];
    cnt += nWaysToTile(next_grid);
  } else if (first_col == ValidColumns[4]) {
    Grid next_grid(grid.begin()+1, grid.end());
    cnt += nWaysToTile(next_grid);
  } else if (first_col == invalid1) {
    Grid next_grid(grid.begin()+1, grid.end());
    next_grid.front() = ValidColumns[2];
    cnt += nWaysToTile(next_grid);
  }

  return cnt;
}

int main()
{
  int N, n = 0, W;
  cin >> N;
  while (N--) {
    cin >> W;

    Grid grid(W, {0, 0, 0, 0});
    cout << ++n << ' ' << nWaysToTile(grid) << endl;
  }
  return 0;
}
