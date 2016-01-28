#include <iostream>
#include <vector>
#include <array>

using namespace std;

using Cell = char;
using Row = vector<Cell>;
using Board = vector<Row>;

using Coord = pair<int, int>;
using Shape = array<Coord, 3>;

const Cell empty('.');
const Cell block('%');

Board board;
size_t C, H, W;

array<Shape, 4> shapes {
  Shape{Coord{0, 0}, {0, 1}, {1, 0}},
  Shape{Coord{0, 0}, {0, 1}, {1, 1}},
  Shape{Coord{0, 0}, {1, 0}, {1, 1}},
  Shape{Coord{0, 0}, {1, 0}, {1,-1}},
};

inline bool available(const size_t row, const size_t col, const Shape &shape)
{
  for (const auto &cell : shape) {
    if ((col == 0 && cell.second == -1) ||  // out of board
        (W <= col + cell.second) ||
        (H <= row + cell.first) ||
        (board[row + cell.first][col + cell.second] != empty)) {
      return false;
    }
  }
  return true;
}

inline bool put(const size_t row, const size_t col, const Shape &shape)
{
  if (!available(row, col, shape)) return false;
  for (const auto &cell : shape) {
    board[row + cell.first][col + cell.second] = block;
  }
  return true;
}

inline void remove(const size_t row, const size_t col, const Shape &shape)
{
  for (const auto &cell : shape) {
    board[row + cell.first][col + cell.second] = empty;
  }
}

size_t count(const size_t row = 0, const size_t col = 0)
{
  if (row == H - 1) {
    for (const auto &cell : board[row]) if (cell == empty) return 0;
    return 1;
  }
  if (col == W) return count(row + 1, 0);
  if (board[row][col] != empty) return count(row, col + 1);

  size_t cnt=0;
  for (const auto &shape : shapes) {
    if (put(row, col, shape)) {
      cnt += count(row, col + 1);
      remove(row, col, shape);
    }
  }
  return cnt;
}

int main()
{
  cin >> C;
  while (C--) {
    cin >> H >> W;

    board.assign(H, Row(W));
    auto emptyCnt = 0;
    for (auto &row : board) {
      for (auto &cell: row) {
        cin >> cell;
        if (cell == empty) ++emptyCnt %= 3;
      }
    }
    cout << (emptyCnt ? 0 : count()) << endl;
  }
  return 0;
}
