// 136493988
#include <algorithm>
#include <iostream>
#include <vector>

const int64_t cInf = 1'000'000'000;
const int64_t cNone = 100'000;

struct Global {
  std::vector<std::vector<int64_t>> matrix;
  std::vector<std::vector<int64_t>> next;
  std::vector<std::vector<std::vector<int64_t>>> dp;
  int64_t cucle_bro = -1;
  bool is_cucle = false;
  Global(int64_t n)
      : matrix(n, std::vector<int64_t>(n)),
        next(n, std::vector<int64_t>(n, -1)),
        dp(n + 1, std::vector<std::vector<int64_t>>(
                      n, std::vector<int64_t>(n, cInf))) {}
};

void Do(int64_t n, Global& info) {
  for (int64_t k = 1; k <= n; ++k) {
    for (int64_t u = 0; u < n; ++u) {
      for (int64_t v = 0; v < n; ++v) {
        int64_t same = info.dp[k - 1][k - 1][v] + info.dp[k - 1][u][k - 1];
        info.dp[k][u][v] = std::min(info.dp[k - 1][u][v], same);
        if (same < info.dp[k - 1][u][v]) {
          info.next[u][v] = info.next[u][k - 1];
        }
        if (u == v && info.dp[k][u][v] < 0) {
          info.cucle_bro = v;
          return;
        }
      }
    }
  }
}

void Input(int64_t n, Global& info) {
  int64_t x = 0;
  for (int64_t i = 0; i < n; ++i) {
    for (int64_t j = 0; j < n; ++j) {
      std::cin >> x;
      info.matrix[i][j] = (x == cNone ? cInf : x);
      info.dp[0][i][j] = x == cNone ? cInf : x;
      info.next[i][j] = x == cNone ? -1 : j;
    }
  }
}

void Output(Global& info) {
  if (info.cucle_bro == -1) {
    std::cout << "NO\n";
  } else {
    std::vector<int64_t> ans;
    int64_t x = info.cucle_bro;
    ans.push_back(x);
    int64_t ne = info.next[x][x];
    while (ne != x) {
      ans.push_back(ne);
      ne = info.next[ne][x];
    }
    ans.push_back(x);
    std::cout << "YES\n" << ans.size() << "\n";
    for (auto v : ans) {
      std::cout << v + 1 << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  int64_t n = 0;
  std::cin >> n;
  Global info(n);
  Input(n, info);
  Do(n, info);
  Output(info);
}
