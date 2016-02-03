#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

using GameBoard = vector<int>;

int play(const GameBoard &board)
{
  const auto &left(board.front()), &right(board.back());

  switch (board.size()) {
    case 0: return 0;
    case 1: return left;
    case 2: return (left > right ? 1 : -1) * (left - right);
  }

  array<int, 4> values {
    left  - play(GameBoard(board.begin()+1, board.end()  )),
    right - play(GameBoard(board.begin()  , board.end()-1)),
          - play(GameBoard(board.begin()+2, board.end()  )),
          - play(GameBoard(board.begin()  , board.end()-2))
  };

  return *max_element(values.begin(), values.end());
}

int main()
{
  int C, n;
  cin >> C;
  while (C--) {
    cin >> n;

    GameBoard board(n);
    for (auto &cell : board) cin >> cell;
    cout << play(board) << endl;
  }
  return 0;
}
