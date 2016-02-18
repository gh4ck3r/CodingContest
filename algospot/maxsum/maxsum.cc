#include <iostream>
#include <vector>

using namespace std;

using Sequence = vector<int>;

int main()
{
  size_t T, N;
  cin >> T;
  while (T--) {
    cin >> N;
    Sequence seq(N);
    for (auto &n : seq) cin >> n;
    // XXX
  }
  return 0;
}
