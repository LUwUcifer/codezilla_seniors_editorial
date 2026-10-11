#include <bits/stdc++.h>
using namespace std;

int n;
set<int> d; // difference positions
multiset<int> sub; // substring lengths

void flip(int x) {
  if (x == 0 || x == n)
    return;
  auto i = d.find(x);
  if (i == d.end()) { // split segment
    i = d.insert(x).first;
    int l = *prev(i), r = *next(i);
    sub.erase(sub.find(r - l));
    sub.insert(x - l);
    sub.insert(r - x);
  } else { // merge segment
    int l = *prev(i), r = *next(i);
    d.erase(i);
    sub.insert(r - l);
    sub.erase(sub.find(x - l));
    sub.erase(sub.find(r - x));
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s; cin >> s;
  n = (int) s.size();
  d.insert(0);
  d.insert(n);

  for (int i = 1; i < n; i++)
    if (s[i] != s[i - 1])
      d.insert(i);
  for (auto i = ++d.begin(); i != d.end(); i++)
    sub.insert(*i - *prev(i));

  int m; cin >> m;
  while (m--) {
    int x; cin >> x;
    flip(x), flip(x - 1);
    cout << *sub.rbegin() << (m ? ' ' : '\n');
  }
}