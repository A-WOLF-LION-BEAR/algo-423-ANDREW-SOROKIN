// 138134942
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const int64_t cInf = 1'000'000'000'000;

struct Edga {
  int64_t to = -1;
  int64_t cost = 0;
  int64_t flow = 0;
  int64_t cap = 0;
  int64_t rev_idx = -1;
  bool is_reversed = false;
  Edga(int64_t to, int64_t cost, int64_t cap, int64_t rev_idx, bool is_rev)
      : to(to), cost(cost), cap(cap), rev_idx(rev_idx), is_reversed(is_rev) {}
};

struct Global {
  std::vector<std::vector<Edga>> matrix;
  std::vector<int64_t> dist;
  std::vector<int64_t> parent;
  std::vector<int64_t> parent_edga;
  int64_t n;
  Global(int64_t n)
      : matrix(n), dist(n, cInf), parent(n, -1), parent_edga(n, -1), n(n) {}
};

bool De(Global& info, int64_t s, int64_t t) {
  info.dist = std::vector<int64_t>(info.n, cInf);
  info.parent = std::vector<int64_t>(info.n, -1);
  info.parent_edga = std::vector<int64_t>(info.n, -1);
  std::queue<int64_t> q;
  std::vector<bool> in_queue(info.n, false);
  info.dist[s] = 0;
  q.push(s);
  in_queue[s] = true;
  while (!q.empty()) {
    int64_t u = q.front();
    q.pop();
    in_queue[u] = false;
    for (size_t i = 0; i < info.matrix[u].size(); ++i) {
      if (info.matrix[u][i].cap > info.matrix[u][i].flow &&
          info.dist[u] + info.matrix[u][i].cost <
              info.dist[info.matrix[u][i].to]) {
        info.dist[info.matrix[u][i].to] = info.dist[u] + info.matrix[u][i].cost;
        info.parent[info.matrix[u][i].to] = u;
        info.parent_edga[info.matrix[u][i].to] = i;
        if (!in_queue[info.matrix[u][i].to]) {
          q.push(info.matrix[u][i].to);
          in_queue[info.matrix[u][i].to] = true;
        }
      }
    }
  }
  return info.dist[t] != cInf;
}

int64_t MinCostMaxFlow(Global& info, int64_t s, int64_t t) {
  int64_t total_cost = 0;
  while (De(info, s, t)) {
    int64_t flow = cInf;
    for (int64_t v = t; v != s; v = info.parent[v]) {
      int64_t u = info.parent[v];
      int64_t edge_idx = info.parent_edga[v];
      flow = std::min(
          flow, info.matrix[u][edge_idx].cap - info.matrix[u][edge_idx].flow);
    }
    for (int64_t v = t; v != s; v = info.parent[v]) {
      int64_t u = info.parent[v];
      int64_t edge_idx = info.parent_edga[v];
      info.matrix[u][edge_idx].flow += flow;
      info.matrix[v][info.matrix[u][edge_idx].rev_idx].flow -= flow;
      total_cost += flow * info.matrix[u][edge_idx].cost;
    }
  }
  return total_cost;
}

void Input(int64_t m, Global& info) {
  int64_t u = 0;
  int64_t v = 0;
  int64_t c = 0;
  int64_t w = 0;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> u >> v >> c >> w;
    info.matrix[u - 1].emplace_back(v - 1, w, c, info.matrix[v - 1].size(),
                                    false);
    info.matrix[v - 1].emplace_back(u - 1, -w, 0, info.matrix[u - 1].size() - 1,
                                    true);
  }
}

int main_KKKKKKK() {
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  Global info(n);
  Input(m, info);
  std::cout << MinCostMaxFlow(info, 0, n - 1) << "\n";
}
