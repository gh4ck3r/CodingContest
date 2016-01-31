#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

#define DEBUG
using namespace std;

using Sequence = list<int>;

int max_subseq(const Sequence &seq)
{
  vector<Sequence> inc_seqs;

  Sequence sub_seq;
  int prev = 0;
  for (const auto &n : seq) {
    if (n <= prev) inc_seqs.push_back(move(sub_seq));
    sub_seq.push_back(n);
    prev = n;
  }
  if (!sub_seq.empty()) inc_seqs.push_back(move(sub_seq));

  Sequence max_seq;
  for (auto &s : inc_seqs) {
#ifdef DEBUG
    clog << "max : ";
    for (const auto &n : max_seq) clog << n << ' ';
    clog << endl << "  s : ";
    for (const auto &n : s) clog << n << ' '; clog << endl;
#endif
    if (max_seq.empty()) max_seq = s;
    else {
      auto find_bigger = [](Sequence &s, const int &p) {
        return find_if(s.begin(), s.end(),
                       [&p](const int n) {return p <= n;});
      };

      auto i1(find_bigger(max_seq, s.front()));
      auto i2(find_bigger(s, max_seq.back()));
      decltype(i1) i3;

      auto d1(distance(i1, max_seq.end()));
      auto d2(distance(s.begin(), i2));
#ifdef DEBUG
      clog << " i1 : " << *i1 << ", i2 : " << (i2==s.end()?0:*i2) << endl;
      clog << " d1 : " << d1 << ", d2 : " << d2 << endl;
#endif
      if (d1 == d2) {
        while (!max_seq.empty() && s.front() <= max_seq.back()) max_seq.pop_back();
        i3 = s.begin();
      } else if (d1 < d2) {
        i3 = s.begin();
        max_seq.erase(i1, max_seq.end());
      } else {
        if (i2 != s.end() && *i2 == max_seq.back()) ++i2;
        i3 = i2;
      }
      max_seq.insert(max_seq.end(), i3, s.end());
    }

#ifdef DEBUG
    clog << " ** max_seq : ";
    for (const auto &n : max_seq) clog << n << ' ';
    clog << endl;
    clog << "--------------------" << endl;
#endif
  }

#ifdef DEBUG
    clog << "max_seq : ";
    for (const auto &n : max_seq) clog << n << ' ';
    clog << endl;
#endif
  return max_seq.size();
}

int main()
{
  int C, N;
  cin >> C;
  while(C--) {
    cin >> N;
    Sequence seq(N);
    for (auto &n : seq) cin >> n;
#ifdef DEBUG
    clog << "====================" << endl;
    for (const auto &n : seq) clog << n << ' ';
    clog << endl << "--------------------" << endl;
#endif
    cout << max_subseq(seq) << endl;
#ifdef DEBUG
    clog << "====================" << endl;
#endif
  }
  return 0;
}
