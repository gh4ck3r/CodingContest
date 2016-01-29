#include <iostream>
#include <stack>
#include <map>

using namespace std;

using Coin = size_t;
using CoinBox = stack<Coin>;

using Key = pair<size_t, CoinBox>;
map<Key, size_t> memoize;

size_t make_changes(const size_t changes, CoinBox coinbox)
{
  if (changes == 0) return 1;
  if (coinbox.size() == 1) return changes % coinbox.top() == 0;

  Key memo_key(changes, coinbox);
  if (memoize[memo_key]) return memoize[memo_key];

  while (!coinbox.empty() && changes < coinbox.top()) coinbox.pop();
  if (coinbox.empty()) return 0;
  const Coin &topcoin(coinbox.top());
  if (changes < topcoin) return 0;

  size_t cnt = make_changes(changes - topcoin, coinbox);
  coinbox.pop();
  cnt += make_changes(changes, coinbox);

  memoize[memo_key] = cnt;
  return cnt;
}

int main()
{
  size_t T, M, C;

  cin >> T;
  while (T--) {
    CoinBox coinbox;
    memoize.clear();

    cin >> M >> C;
    while (C--) {
      Coin coin;
      cin >> coin;
      // ASSERT : coin list is sorted
      if (!coinbox.empty() && coin < coinbox.top()) return -1;
      coinbox.push(coin);
    }

    cout << make_changes(M, coinbox) % 1000000007 << endl;
  }
  return 0;
}
