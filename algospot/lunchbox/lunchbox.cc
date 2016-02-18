#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct Lunch : public pair<int&, int&> {
  Lunch() : pair(e, m){}
  int m, e;
};

int main()
{
  size_t T, N;
  cin >> T;
  while (T--) {
    cin >> N;

    vector<Lunch> lunches(N);
    for (auto &l : lunches) cin >> l.m;
    for (auto &l : lunches) cin >> l.e;

    sort(lunches.begin(), lunches.end(), [](const Lunch &l1, const Lunch &l2) {
		return l1.e > l2.e;
	});

    size_t m_time(0), e_time(0);
    for (const auto &l : lunches) {
      m_time += l.m;
      e_time = max(e_time, m_time + l.e);
    }

    cout << e_time << endl;
  }

  return 0;
}
