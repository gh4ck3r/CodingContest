#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  int C, N;
  cin >> C;
  while (C--) {
    cin >> N;

    vector<int> seq(N);
    for (auto &n : seq) cin >> n;

    // lis(n) = { 1 + max(lis(j)) }, where j < i and seq[j] < seq[i]
    //          or 1 if there's no such j
    vector<int> lis(N);
    lis[0] = 1;
    for (auto i = 1; i < N; ++i) {
      auto max_lis = 0;
      for (auto j = 0; j < i; ++j) {
        if (seq[j] < seq[i] && max_lis < lis[j]) {
          max_lis = lis[j];
        }
      }
      lis[i] = 1 + max_lis;
    }

    cout << *max_element(lis.begin(), lis.end()) << endl;
  }

  return 0;
}

