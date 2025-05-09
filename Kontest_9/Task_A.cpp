// 137098404
#include <iostream>
#include <vector>

struct Global {
  std::vector<std::vector<int64_t>> matrix;
  std::vector<int64_t> match;
  std::vector<bool> used;
  std::vector<bool> con;
  Global(int64_t n, int64_t k)
      : matrix(n), match(k, -1), used(n, false), con(n, false) {}
};

bool Augment(int64_t v, Global& info) {
  if (info.used[v]) {
    return false;
  }
  info.used[v] = true;
  for (auto to : info.matrix[v]) {
    if (info.match[to] == -1 || Augment(info.match[to], info)) {
      info.match[to] = v;
      return true;
    }
  }
  return false;
}

void Kun(int64_t n, Global& info) {
  for (int64_t v = 0; v < n; ++v) {
    if (Augment(v, info)) {
      info.used = info.con;
    }
  }
}

void Input(int64_t n, Global& info) {
  int64_t c = -1;
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> c;
    while (c != 0) {
      info.matrix[i].push_back(c - 1);
      std::cin >> c;
    }
  }
}

void Output(Global& info) {
  int64_t len = 0;
  for (int64_t i = 0; i < int64_t(info.match.size()); ++i) {
    if (info.match[i] != -1) {
      ++len;
    }
  }
  std::cout << len << "\n";
  for (int64_t i = 0; i < int64_t(info.match.size()); ++i) {
    if (info.match[i] != -1) {
      std::cout << info.match[i] + 1 << " " << i + 1 << "\n";
    }
  }
}

int main() {
  int64_t n = 0;
  int64_t k = 0;
  std::cin >> n >> k;
  Global info(n, k);
  Input(n, info);
  Kun(n, info);
  Output(info);
}
