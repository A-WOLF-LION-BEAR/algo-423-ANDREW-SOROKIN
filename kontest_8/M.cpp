// 136496185
#include <algorithm>
#include <iostream>
#include <vector>

class Sds {
 private:
  std::vector<std::vector<int64_t>> sds_;
  std::vector<int64_t> parents_;
  std::vector<int64_t> sizes_;

 public:
  Sds(int64_t n) : parents_(n, -1), sizes_(n, 1) {}

  int64_t Get(int64_t v) {
    if (parents_[v] == -1) {
      return v;
    }
    int64_t root = Get(parents_[v]);
    parents_[v] = root;
    return root;
  }

  void Unite(int64_t u, int64_t v) {
    u = Get(u);
    v = Get(v);
    if (u != v) {
      if (sizes_[u] < sizes_[v]) {
        std::swap(u, v);
      }
      parents_[v] = u;
      sizes_[u] += sizes_[v];
    }
  }

  bool Ask(int64_t u, int64_t v) { return Get(u) == Get(v); }
};

bool SortRule(std::vector<int64_t> a, std::vector<int64_t> b) {
  return a[2] < b[2];
}

struct Global {
  std::vector<std::vector<int64_t>> edge;  // {u, v, c}
  int64_t weight = 0;
};

void Input(int64_t m, Global& info) {
  int64_t u = 0;
  int64_t v = 0;
  int64_t c = 0;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> u >> v >> c;
    info.edge.push_back({u - 1, v - 1, c});
  }
  std::sort(info.edge.begin(), info.edge.end(), SortRule);
}

void Kuskal(Sds& sds, Global& info) {
  for (auto x : info.edge) {
    if (sds.Get(x[0]) != sds.Get(x[1])) {
      info.weight += x[2];
      sds.Unite(x[0], x[1]);
    }
  }
  std::cout << info.weight << "\n";
}

int main() {
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  Sds sds(n);
  Global info;
  Input(m, info);
  Kuskal(sds, info);
}
