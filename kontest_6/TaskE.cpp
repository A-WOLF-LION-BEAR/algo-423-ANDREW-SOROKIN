// 133100419
#include <iostream>
#include <vector>

struct Node {
  std::vector<int> things;
  int sum_prices = 0;
};

void Input(std::vector<int>& weights, std::vector<int>& prices, int n) {
  for (int i = 0; i < n; ++i) {
    std::cin >> weights[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> prices[i];
  }
}
void Build(std::vector<std::vector<Node>>& dp, std::vector<int>& weights,
           std::vector<int>& prices, int n, int m) {
  int plus_a = 0;
  for (int a = 0; a <= m; ++a) {
    for (int i = 1; i <= n; ++i) {
      if (a >= weights[i - 1]) {
        plus_a = dp[i - 1][a - weights[i - 1]].sum_prices + prices[i - 1];
        if (plus_a > dp[i - 1][a].sum_prices) {
          dp[i][a].sum_prices = plus_a;
          dp[i][a].things = dp[i - 1][a - weights[i - 1]].things;
          dp[i][a].things.push_back(i);
        } else {
          dp[i][a] = dp[i - 1][a];
        }
      } else {
        dp[i][a] = dp[i - 1][a];
      }
    }
  }
}
void GetAns(std::vector<std::vector<Node>>& dp, int n, int m) {
  int ans = 0;
  for (int i = 0; i <= m; ++i) {
    ans = dp[n][i].sum_prices >= dp[n][ans].sum_prices ? i : ans;
  }
  for (int i : dp[n][ans].things) {
    std::cout << i << "\n";
  }
}
void Print(std::vector<std::vector<Node>>& dp, int n, int m) {
  std::cout << "\n";
  for (int a = 0; a <= m; ++a) {
    // for (int i = 0; i <= n; ++i) {
    //   std::cout << a << " ";
    // }
    std::cout << "       ";
    for (int i = 0; i <= n; ++i) {
      std::cout << dp[i][a].sum_prices << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<int> weights(n);
  std::vector<int> prices(n);
  std::vector<std::vector<Node>> dp(n + 1, std::vector<Node>(m + 1));
  Input(weights, prices, n);
  Build(dp, weights, prices, n, m);
  // Print(dp, n, m);
  GetAns(dp, n, m);
}
