//129999398
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

const int cB = 100;
const int cE = 65000;
const uint64_t cP = 274876858367;
const uint64_t cSize = 1000000;

struct Node {
  bool head = true;
  uint64_t x;
  int hash;
  int dad = 0;
  int ind = 0;
};
int Random() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(cB, cE);
  return dist(gen);
}
uint64_t ToHash(int a, int b, uint64_t x) { return (a * x + b) % cP % cSize; }
int Find(int a, int b, uint64_t x, std::vector<std::vector<Node>>& hash_table) {
  uint64_t ind = ToHash(a, b, x);
  for (int i = 0; i < int(hash_table[ind].size()); ++i) {
    if (hash_table[ind][i].x == x) {
      return i;
    }
  }
  return -1;
}
void Push(int a, int b, uint64_t x,
          std::vector<std::vector<Node>>& hash_table) {
  Node s;
  s.hash = ToHash(a, b, x);
  s.head = hash_table[s.hash].empty();
  s.x = x;
  s.ind = hash_table[s.hash].size();
  s.dad = s.head ? -1 : hash_table[s.hash][hash_table[s.hash].size() - 1].ind;
  hash_table[s.hash].push_back(s);
}
void Delet(int a, int b, uint64_t x, std::vector<std::vector<Node>>& hash_table,
           int ind) {
  int indhash = ToHash(a, b, x);
  if (hash_table[indhash].size() == 1) {
    hash_table[indhash].clear();
  } else if (ind == 0) {
    hash_table[indhash][ind + 1].head = true;
    hash_table[indhash].erase(hash_table[indhash].begin());
  } else if (ind == int(hash_table[indhash].size()) - 1) {
    hash_table[indhash].erase(hash_table[indhash].end());
  } else {
    hash_table[indhash][ind + 1].dad = hash_table[indhash][ind].dad;
    hash_table[indhash].erase(hash_table[indhash].begin() + ind);
  }
}
void Body() {
  std::vector<std::vector<Node>> hash_table(cSize);
  int n;
  std::cin >> n;
  int a = Random();
  int b = Random();
  char c;
  uint64_t x;
  for (int i = 0; i < n; ++i) {
    std::cin >> c >> x;
    if (c == '+') {
      int ind = Find(a, b, x, hash_table);
      if (ind == -1) {
        Push(a, b, x, hash_table);
      }
    } else if (c == '-') {
      int ind = Find(a, b, x, hash_table);
      if (ind != -1) {
        Delet(a, b, x, hash_table, ind);
      }
    } else if (c == '?') {
      std::cout << (Find(a, b, x, hash_table) == -1 ? "NO\n" : "YES\n");
    }
  }
}
int main() { Body(); }
