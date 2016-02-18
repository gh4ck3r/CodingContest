#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
  size_t T, N;
  cin >> T;
  while (T--) {
    cin >> N;

    int n, maxSum(0), subSum(0);
    while (N--) {
      cin >> n;
      subSum = max(0, subSum + n);
      maxSum = max(maxSum, subSum);
    }

    cout << maxSum << endl;
  }
  return 0;
}
