// 136166134
#include <iostream>
#include <queue>
#include <vector>

const int64_t cInf = 2009000999;

struct Global {
  std::vector<std::vector<std::pair<int64_t, int64_t>>> matrix;  // {v, cost}
  std::vector<int64_t> dist;
  Global(int64_t n) : matrix(n), dist(n, cInf) {}
};

void Do(int64_t s, Global& info) {
  std::priority_queue<std::pair<int64_t, int64_t>,
                      std::vector<std::pair<int64_t, int64_t>>,
                      std::greater<std::pair<int64_t, int64_t>>>
      pq;
  pq.push({0, s});
  while (!pq.empty()) {
    auto [current_dist, u] = pq.top();
    pq.pop();
    if (current_dist > info.dist[u]) {
      continue;
    }
    for (auto to : info.matrix[u]) {
      int64_t y = info.dist[u] + to.second;
      if (y < info.dist[to.first]) {
        info.dist[to.first] = y;
        pq.push({y, to.first});
      }
    }
  }
}

void Input(int64_t m, int64_t& s, Global& info) {
  int64_t u = 0;
  int64_t v = 0;
  int64_t c = 0;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> u >> v >> c;
    info.matrix[u].push_back({v, c});
    info.matrix[v].push_back({u, c});
  }
  std::cin >> s;
  info.dist[s] = 0;
}

void Output(const Global& info) {
  for (int64_t d : info.dist) {
    std::cout << d << " ";
  }
  std::cout << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int64_t t = 0;
  std::cin >> t;
  for (int i = 0; i < t; ++i) {
    int64_t n = 0;
    int64_t m = 0;
    int64_t s = 0;
    std::cin >> n >> m;
    Global info(n);
    Input(m, s, info);
    Do(s, info);
    Output(info);
  }
}
