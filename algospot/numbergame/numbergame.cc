#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <map>

using namespace std;

using GameBoard = vector<int>;
using Key = pair<int, int>;
map<Key, int> Cache;

int play(const GameBoard &board, const int &begin, const int &len)
{
  Key key(begin, len);
  if (Cache[key]) return Cache[key];

  const auto &left(board[begin]), &right(board[begin + len - 1]);

  switch (len) {
    case 0: return Cache[key] = 0;
    case 1: return Cache[key] = left;
    case 2: return Cache[key] = (left > right ? 1 : -1) * (left - right);
  }

  array<int, 4> values {
    left  - play(board, begin+1, len-1),
    right - play(board, begin  , len-1),
          - play(board, begin+2, len-2),
          - play(board, begin  , len-2)
  };

  return Cache[key] = *max_element(values.begin(), values.end());
}

int main()
{
  int C, n;
  cin >> C;
  while (C--) {
    cin >> n;

    Cache.clear();
    GameBoard board(n);
    for (auto &cell : board) cin >> cell;

    cout << play(board, 0, board.size()) << endl;
  }
  return 0;
}
