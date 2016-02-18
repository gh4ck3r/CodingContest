#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
  size_t c, n;
  cin >> c;
  while (c--) {
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> lengths;
    while (n--) {
      int l;
      cin >> l;
      lengths.push(l);
    }

    auto cost(0);
    while (lengths.size() > 1) {
      auto l1(lengths.top());
      lengths.pop();
      auto l2(lengths.top());
      lengths.pop();
      auto l3(l1+l2);
      lengths.push(l3);
      cost += l3;
    }
    cout << cost << endl;
  }
  return 0;
}
