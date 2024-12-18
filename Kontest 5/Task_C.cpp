//130050869
#include <iostream>
#include <random>
#include <string>
#include <vector>

const int cB = 100;
const int cE = 4500;
const int cP = 433494437;
const int cSize = 514229;

int Random() {
  std::random_device shkebede;
  std::mt19937 gen(shkebede());
  std::uniform_int_distribution<> dist(cB, cE);
  return dist(gen);
}
int FindNum(std::vector<char>& alf, char c, int a) {
  for (int i = 0; i < int(alf.size()) - 1; ++i) {
    if (alf[i] == c) {
      return (a + i + 1) * (a + i + 1);
    }
  }
  alf.push_back(c);
  return (a + alf.size()) * (a + alf.size());
}
int ToHash(std::string s, int a) {
  std::vector<char> alf;
  int ans = 0;
  for (int i = 0; i < int(s.size()); ++i) {
    ans += FindNum(alf, s[i], a);
    if (ans > cP) {
      ans -= cP;
    }
  }
  return ans % cSize;
}
int CharIn(std::vector<char>& alf, char c) {
  for (int i = 0; i < int(alf.size()); ++i) {
    if (alf[i] == c) {
      return i + 1;
    }
  }
  alf.push_back(c);
  return int(alf.size());
}
bool StupidCheck(std::string s1, std::string s2) {
  bool ans = true;
  if (s1.size() != s2.size()) {
    ans = false;
  } else {
    std::vector<char> alf1;
    std::vector<char> alf2;
    for (int i = 0; i < int(s1.size()); ++i) {
      if (CharIn(alf1, s1[i]) != CharIn(alf2, s2[i])) {
        ans = false;
      }
    }
  }
  return ans;
}
bool Find(std::string s, int a,
          std::vector<std::vector<std::string>>& hash_table, bool put) {
  int ind = ToHash(s, a);
  for (int i = 0; i < int(hash_table[ind].size()); ++i) {
    if (StupidCheck(s, hash_table[ind][i])) {
      return true;
    }
  }
  if (put) {
    hash_table[ind].push_back(s);
  }
  return false;
}
void Body() {
  std::vector<std::vector<std::string>> hash_table(cSize);
  int n;
  int a;
  char c;
  std::string s;
  a = Random();
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> c >> s;
    if (c == '?') {
      std::cout << (Find(s, a, hash_table, false) ? "YES\n" : "NO\n");
    } else if (c == '+') {
      Find(s, a, hash_table, true);
    }
  }
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  Body();
}
