/*************************************************************************
  >         File: PairedBoardGrouper.cc
  >       Author: Yuan Lei
  >         Mail: yuanlei@fb.com
  > Created Time: Sat 11 Jan 11:06:56 2020
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

const std::string cards[2] = {"AKQJT", "23456789"};

int getRank(char c) {
  if (c == 'A') return 14;
  if (c == 'K') return 13;
  if (c == 'Q') return 12;
  if (c == 'J') return 11;
  if (c == 'T') return 10;
  return c - '0';
}

int main() {
  // AAB 
  // A'rank, B'rank, AB connected
  std::vector<std::string> board[2][2][2]; 
  std::ios::sync_with_stdio(0);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      for (auto a: cards[i]) {
        for (auto b: cards[j]) {
          if (a == b) continue;
          std::string s;
          s = s + a + 'c' + a + 'h' + b + "h:1";
          board[i][j][std::abs(getRank(a) - getRank(b)) < 5].push_back(s);
        }
      }
    }
  }

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      for (int k = 0; k < 2; ++k) {
        std::string s = i == 1 ? "Low" : "High";
        s += "Paired_";
        s += j == 1 ? "Low" : "High";
        s += "_";
        s += k == 1 ? "Connected" : "Disconnected";
        s += "_2tone";
        std::cerr << s << " has " << board[i][j][k].size() << " entries." << std::endl;
        freopen(s.c_str(), "w", stdout);
        for (auto entry: board[i][j][k]) {
          std::cout << entry << std::endl;
        }
        fclose(stdout);
      }
    }
  }

  return 0;
}
