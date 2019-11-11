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

/* 
 * # Input
 * Html 代码中 body>page>main>preflopTable_Results>ResultsInner>pfa_tc div.
 * <div class="pfa_tc">
 * 	<table>
 * 			<tbody><tr><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td></tr>
 * 			<tr><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
 * 			<tr><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td class="r"></td><td>4</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
 * 			<tr><td class="r"></td><td class="r"></td><td>24</td><td class="r"></td><td class="r"></td><td class="r"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
 * 			<tr><td class="r"></td><td></td><td></td><td></td><td class="r"></td><td class="r"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
 * 			<tr><td></td><td></td><td></td><td></td><td></td><td class="r"></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
 * 			<tr><td></td><td></td><td></td><td></td><td></td><td></td><td class="r"></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
 * 			<tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td class="r"></td><td></td><td></td><td></td><td></td><td></td></tr>
 * 			<tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td class="r"></td><td></td><td></td><td></td><td></td></tr>
 * 			<tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td class="r"></td><td></td><td></td><td></td></tr>
 * 			<tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
 * 			<tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
 * 			<tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
 * 		</tbody></table>
 * </div>
 *
 * # Output
 * Text Pio importable. Format: AA,KK:0.8,...
 *   一个 entry 表示一个手牌的 open 频率, 没有键值默认频率是 1, 
 *   否则浮点数代表频率, 逗号分隔
 */

const std::string HEAD = "<tbody>";
const std::string TAIL = "</tbody>";
const std::string ENTRY = "</td>";
const std::string RAISE = "class=\"r\"";
const std::string CALL = "class=\"c\"";

std::string getNext(std::string& s) {
  auto pos = s.find(ENTRY);
  if (pos == std::string::npos) return "";
  auto answer = s.substr(0, pos + ENTRY.size());
  s = s.substr(pos + ENTRY.size());
  return answer;
}

// type 0: raise freq, type 1: call freq
double getFreq(std::string& token, int type = 0) {
  if (type == 0 && token.find(RAISE) != std::string::npos) {
    return 1.0;
  } else if (type == 0) {
    auto pos = token.find('>');
    if (token[pos + 1] != '<') {
      auto nextPos = token.find(pos + 1, '<');
      auto freq = token.substr(pos + 1, nextPos - pos);
      return 1.0 * std::stoi(freq) / 100;
    }
    return 0;
  } else if (type == 1 && token.find(CALL) != std::string::npos) {
    auto pos = token.find('>');
    if (token[pos + 1] != '<') {
      auto nextPos = token.find(pos + 1, '<');
      auto freq = token.substr(pos + 1, nextPos - pos);
      return 1.0 - 1.0 * std::stoi(freq) / 100;
    }
    return 1.0;
  }
  return 0;
}

char getCard(int id) {
  if (id == 14) return 'A';
  else if (id == 13) return 'K';
  else if (id == 12) return 'Q';
  else if (id == 11) return 'J';
  else if (id == 10) return 'T';
  else return id + '0';
}

std::string getEntry(int a, int b, double freq) {
  std::string answer;
  answer += getCard(a);
  answer += getCard(b);
  if (a > b) answer += 's';
  else if (a < b) {
    std::swap(answer[0], answer[1]);
    answer += 'o';
  }
  if (std::abs(1.0 - freq) > 1e-7 && freq > 1e-7) {
    answer += ':';
    answer += std::to_string(freq);
  }
  answer += ',';
  if (freq < 1e-7) answer = "";
  return answer;
}

int main(int argc, char* argv[]) {
  std::ios::sync_with_stdio(0);
  std::string s;
  bool ready = 0;
  int row = 14;
  while (std::getline(std::cin, s)) {
    std::stringstream sin(s);
    auto pos = s.find(HEAD);
    if (pos != std::string::npos) {
      ready = 1;
      s = s.substr(pos);
      if (s.empty()) continue;
    }
    if (s.find(TAIL) != std::string::npos) {
      break;
    }
    if (ready) {
      for (int col = 14; col >= 2; --col) {
        auto token = getNext(s);
        auto freq = getFreq(token, argv[1][0] - '0');
        std::cout << getEntry(row, col, freq);
      }
      --row;
    }
  }

  return 0;
}
