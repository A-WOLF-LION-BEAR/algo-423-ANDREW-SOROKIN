//130047979

#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

const int cB = 100;
const int cE = 45000;
const int cP = 433494437;
const int cSize = 514229;

struct Node {
  int x;
  int hash;
  int kol = 0;
};
int Random() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(cB, cE);
  return dist(gen);
}
int ToHash(int a, int b, int x) { return abs((a * x + b) % cP % cSize); }
int Find(int a, int b, int x, std::vector<std::vector<Node>>& hash_table) {
  int ind = ToHash(a, b, x);
  for (int i = 0; i < int(hash_table[ind].size()); ++i) {
    if (hash_table[ind][i].x == x && hash_table[ind][i].kol > 0) {
      return i;
    }
  }
  return -1;
}
void Push(int a, int b, int x, std::vector<std::vector<Node>>& hash_table) {
  int f = Find(a, b, x, hash_table);
  int hash = ToHash(a, b, x);
  if (hash_table.empty() || f == -1) {
    Node s;
    s.hash = hash;
    s.x = x;
    s.kol = 1;
    hash_table[s.hash].push_back(s);
  } else {
    ++hash_table[hash][f].kol;
  }
}
void Output(int kolvo, std::vector<int> answers) {
  std::cout << kolvo << "\n";
  for (auto i : answers) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}
void Body() {
  std::vector<std::vector<Node>> hash_table(cSize);
  int n;
  std::cin >> n;
  int a = Random();
  int b = Random();
  int x;
  for (int i = 0; i < n; ++i) {
    std::cin >> x;
    Push(a, b, x, hash_table);
  }
  int q;
  std::cin >> q;
  int kolvo = 0;
  std::vector<int> answers;
  for (int i = 0; i < q; ++i) {
    std::cin >> x;
    int f = Find(a, b, x, hash_table);
    int hash = ToHash(a, b, x);
    if (f != -1) {
      ++kolvo;
      --hash_table[hash][f].kol;
      answers.push_back(hash_table[hash][f].x);
    }
  }
  Output(kolvo, answers);
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  Body();
}
