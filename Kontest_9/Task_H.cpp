// 138133726
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const int64_t cInf = 2'000'000'000;

struct Edga {
  int64_t to = -1;
  int64_t cost = 0;
  int64_t flow;
  int64_t num_e = -1;
  int64_t num_back = -1;
  bool is_rev;
  Edga(int64_t to, int64_t cost, int64_t num, int64_t num_b, bool is_r)
      : to(to),
        cost(cost),
        flow(0),
        num_e(num),
        num_back(num_b),
        is_rev(is_r) {}
};

struct Global {
  std::vector<std::vector<Edga>> matrix;
  std::vector<int64_t> dist;
  std::vector<bool> used;
  std::vector<int64_t> ptr;
  int64_t n;
  Global(int64_t n)
      : matrix(n), dist(n, cInf), used(n, false), ptr(n, 0), n(n) {}
};

void Input(int64_t m, Global& info) {
  int64_t u = 0;
  int64_t v = 0;
  int64_t c = 0;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> u >> v >> c;
    info.matrix[u - 1].push_back(
        Edga(v - 1, c, i, info.matrix[v - 1].size(), false));
    info.matrix[v - 1].push_back(
        Edga(u - 1, 0, i, info.matrix[u - 1].size() - 1, true));
  }
}

bool Bfs(Global& info) {
  std::queue<int64_t> queue;
  queue.push(0);
  info.dist = std::vector<int64_t>(info.n, cInf);
  info.dist[0] = 0;
  while (!queue.empty()) {
    int64_t v = queue.front();
    queue.pop();
    for (auto to : info.matrix[v]) {
      if (to.cost > to.flow && info.dist[to.to] == cInf) {
        info.dist[to.to] = info.dist[v] + 1;
        queue.push(to.to);
      }
    }
  }
  return info.dist[info.n - 1] != cInf;
}

int64_t Dfs(int64_t v, Global& info, int64_t cost = cInf) {
  if (v == info.n - 1 || cost == 0) {
    return cost;
  }
  for (size_t to = info.ptr[v]; to < info.matrix[v].size();
       ++to, ++info.ptr[v]) {
    if (info.dist[info.matrix[v][to].to] == info.dist[v] + 1) {
      int64_t flow = Dfs(
          info.matrix[v][to].to, info,
          std::min(cost, info.matrix[v][to].cost - info.matrix[v][to].flow));
      if (flow != 0) {
        info.matrix[v][to].flow += flow;
        info.matrix[info.matrix[v][to].to][info.matrix[v][to].num_back].flow -=
            flow;
        return flow;
      }
    }
  }
  return 0;
}

int64_t FindMaxFlow(Global& info) {
  int64_t result = 0;
  while (Bfs(info)) {
    info.ptr = std::vector<int64_t>(info.ptr.size(), 0);
    int64_t flow = Dfs(0, info);
    while (flow != 0) {
      result += flow;
      flow = Dfs(0, info);
    }
  }
  return result;
}

void GetAns(int64_t m, Global& info) {
  std::vector<int64_t> ans_flow(m, 0);
  for (auto list : info.matrix) {
    for (auto to : list) {
      if (!to.is_rev) {
        ans_flow[to.num_e] = to.flow;
      }
    }
  }
  for (auto i : ans_flow) {
    std::cout << i << "\n";
  }
}

int main() {
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  Global info(n);
  Input(m, info);
  std::cout << FindMaxFlow(info) << "\n";
  GetAns(m, info);
}
