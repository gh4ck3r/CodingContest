#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <cstring>

using namespace std;

using GameBoard = vector<int>;

#define MAX_N 50
int main()
{
  int C, n;
  cin >> C;
  while (C--) {
    cin >> n;

    GameBoard board(n);
    for (auto &cell : board) cin >> cell;

    int P[MAX_N + 1][MAX_N + 1];
    memset(P, 0, sizeof(P));
    for (auto len=1;len<=n;++len) {
      for (auto beg=0;beg<n;++beg) {
        auto &p(P[beg][len]);
        auto &left(board[beg]), &right(board[beg+len-1]);
        switch (len) {
          case 0: p = 0;break;
          case 1: p = left;break;
          case 2: p = (left >= right ? 1 : -1) * (left - right);break;
          default:
            array<int, 4> values {
              left  - P[beg + 1][len-1],
              right - P[beg]    [len-1],
                    - P[beg + 2][len-2],
                    - P[beg]    [len-2]
            };
            p = *max_element(values.begin(), values.end());
        }
      }
    }

    cout << P[0][n] << endl;
  }
  return 0;
}
