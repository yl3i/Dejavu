/*************************************************************************
  >         File: PioToProPokerTools.cc
  >       Author: Yuan Lei
  >         Mail: yuanlei@fb.com
  > Created Time: Thu 18 Jun 00:59:06 2020
*************************************************************************/
#include <vector>
#include <cstdio>
#include <bitset>
#include <utility>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <numeric>
#include <set>
#include <map>
#include <deque>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;

string convertKey(string key) {
  if (key.size() == 2) {
    return key;
  } else {
    assert(key.size() == 3);
    assert(key.back() == 'o' || key.back() == 's');
    if (key.back() == 'o') {
      return string(1, key[0]) + "x" + string(1, key[1]) + "y";
    } else {
      return string(1, key[0]) + "x" + string(1, key[1]) + "x";
    }
  }
}

string convert(std::string input) {
  auto pos = input.find(':');
  if (pos == string::npos) {
    return convertKey(input) + "@100";
  } else {
    auto key = input.substr(0, pos);
    auto value = input.substr(pos + 1);
    auto freq = (int) (stod(value) * 100 + 0.5);
    freq = std::min(freq, 100);
    freq = std::max(freq, 1);
    return convertKey(key) + "@" + to_string(freq);
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  string s;
  cin >> s;
  istringstream sin(s);
  string token;
  string answer;
  while (getline(sin, token, ',')) {
    std::cerr << token << std::endl;
    answer += convert(token) + ',';
  }
  answer.pop_back();
  std::cerr << answer << std::endl;
  cout << answer << endl;
  return 0;
}
