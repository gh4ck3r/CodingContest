#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

using Members = vector<int>;

istream &operator>>(istream &is, Members &m)
{
  for (auto &n : m) is >> n;
  sort(m.begin(), m.end());
  return is;
}

int main()
{
  size_t T, N;
  cin >> T;
  while (T--) {
    cin >> N;

    Members male(N), female(N);
    cin >> male >> female;

    auto diff(0);
    while (N--) diff += abs(male[N]-female[N]);
    cout << diff << endl;
  }
  return 0;
}
