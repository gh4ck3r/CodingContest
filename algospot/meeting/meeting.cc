#include <iostream>
#include <vector>

using namespace std;

using Members = vector<int>;

int main()
{
  size_t T, N;
  cin >> T;
  while (T--) {
    cin >> N;

    Members male(N), femail(N);
    for(auto &n:male) cin >> n;
    for(auto &n:femail) cin >> n;
  }
  return 0;
}
