// 138095795
#include <algorithm>
#include <iostream>
#include <vector>

struct Edga {
  int cost = 0;
  int from = -1;
  int to = -1;
  int num = -1;
  int f = 0;
  size_t num_back = -1;
  bool is_reverse = false;
  Edga(int c, int u, int v, int n, int n_b, bool is_r)
      : cost(c), from(u), to(v), num(n), num_back(n_b), is_reverse(is_r) {}
};

struct Global {
  std::vector<std::vector<Edga>> matrix;
  std::vector<bool> used;
  std::vector<bool> used2;
  std::vector<int> ans_e;
  int min = -1;
  int n;
  int ans = 0;
  Global(int n) : matrix(n), used(n, false), used2(n, false), n(n) {}
};

void Input(int m, Global& info) {
  int u = 0;
  int v = 0;
  int c = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v >> c;
    info.matrix[u - 1].push_back(
        Edga(c, u - 1, v - 1, i, info.matrix[v - 1].size(), false));
    info.matrix[v - 1].push_back(
        Edga(0, v - 1, u - 1, i, info.matrix[u - 1].size() - 1, true));
    info.matrix[u - 1].push_back(
        Edga(0, u - 1, v - 1, i, info.matrix[v - 1].size(), true));
    info.matrix[v - 1].push_back(
        Edga(c, v - 1, u - 1, i, info.matrix[u - 1].size() - 1, false));
  }
}

bool Dfs(int v, Global& info) {
  if (v == info.n - 1) {
    info.ans += info.min;
    return true;
  }
  info.used[v] = true;
  for (auto& edga : info.matrix[v]) {
    if (!info.used[edga.to] && edga.cost > 0) {
      info.min = (info.min == -1) ? edga.cost : std::min(info.min, edga.cost);
      if (Dfs(edga.to, info)) {
        edga.cost -= info.min;
        info.matrix[edga.to][edga.num_back].cost += info.min;
        return true;
      }
    }
  }
  return false;
}

void AnotherDfs(int v, Global& info) {
  if (info.used[v]) {
    return;
  }
  info.used[v] = true;
  for (auto& edga : info.matrix[v]) {
    if (edga.cost > 0) {
      AnotherDfs(edga.to, info);
    }
  }
}

void AndAnotherDfs(int v, Global& info) {
  info.used2[v] = true;
  for (auto& edga : info.matrix[v]) {
    if (!info.used2[edga.to]) {
      if (info.matrix[edga.to][edga.num_back].cost > 0) {
        AndAnotherDfs(edga.to, info);
      }
    }
    if (info.used[v] && !info.used[edga.to] && !edga.is_reverse) {
      info.ans_e.push_back(edga.num);
    }
  }
}

void GetAns(Global& info) {
  std::sort(info.ans_e.begin(), info.ans_e.end());
  std::cout << info.ans_e.size() << " " << info.ans << "\n";
  for (auto i : info.ans_e) {
    std::cout << i + 1 << " ";
  }
  std::cout << "\n";
}

void Done(Global& info) {
  while (true) {
    info.min = -1;
    if (!Dfs(0, info)) {
      break;
    }
    info.used = std::vector<bool>(info.n, false);
  }
  info.used = std::vector<bool>(info.n, false);
  AnotherDfs(0, info);
  AndAnotherDfs(0, info);
  GetAns(info);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Global info(n);
  Input(m, info);
  Done(info);
}
