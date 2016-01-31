#include <iostream>
#include <vector>
#include <map>

using namespace std;

using Cell = unsigned int;
using DiamondRow = vector<Cell>;
using Diamond = vector<DiamondRow>;

Diamond diamond;
using Key = pair<size_t, size_t>;
static map<Key, size_t> cache;

size_t max_path(const size_t row = 0, const size_t col = 0)
{
  Key key(row, col);
  if (cache[key]) return cache[key];

  if (row == diamond.size() - 1) return diamond.back().back();
  auto &current_row(diamond[row]);
  auto current_row_siz(current_row.size());
  if (current_row_siz <= col) return 0;

  auto nrow(row+1);
  auto next_row_siz(diamond[nrow].size());

  auto ncol(current_row_siz < next_row_siz ? 1 : -1);
  return cache[key] = current_row[col] +
         max(max_path(nrow, col),
             max_path(nrow, col + ncol));
}

int main()
{
  size_t C, N;
  cin >> C;
  while (C--) {
    cache.clear();
    cin >> N;
    size_t h((N<<1) - 1);
    diamond = Diamond(h);
    for (size_t i = 0; i < h; ++i) {
      size_t w(i < N ? i + 1 : h - i);
      DiamondRow &row(diamond[i]);
      for (size_t j = 0; j < w ; ++j) {
        Cell cell;
        cin >> cell;
        row.push_back(cell);
      }
    }
    cout << max_path() << endl;
  }
  return 0;
}
