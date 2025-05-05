// 133747759
#include <algorithm>
#include <iostream>
#include <vector>

const int cP10 = 10;

int Log(int n) {
  int i = 0;
  int a = 1;
  while (a < n) {
    a *= 2;
    ++i;
  }
  return i;
}

int BinFind(std::vector<std::vector<int>>& dp, int n_i, int k_i) {
  int l = 2;
  int r = n_i - 1;
  int mid = (l + r) / 2;
  while (l + 1 < r) {
    (dp[k_i - 2][mid - 1] - dp[k_i - 1][n_i - mid - 1] > 0 ? r : l) = mid;
    mid = (l + r) / 2;
  }
  return std::max(dp[k_i - 2][mid - 1], dp[k_i - 1][n_i - mid - 1]) + 1;
}

void GetAns(int n, int k) {
  if (k == 0) {
    std::cout << (n <= 1 ? 0 : -1) << "\n";
  } else {
    k = std::min(Log(n) + cP10, k);
    std::vector<std::vector<int>> dp(k, std::vector<int>(n));
    for (int k_i = 1; k_i <= k; ++k_i) {
      for (int n_i = 1; n_i <= n; ++n_i) {
        if (k_i == 1) {
          dp[k_i - 1][n_i - 1] = n_i - 1;
        } else if (n_i == 1) {
          dp[k_i - 1][n_i - 1] = 0;
        } else if (n_i == 2) {
          dp[k_i - 1][n_i - 1] = 1;
        } else {
          dp[k_i - 1][n_i - 1] = BinFind(dp, n_i, k_i);
        }
      }
    }
    std::cout << dp[k - 1][n - 1] << "\n";
  }
}

int main() {
  int n = 0;
  int k = 0;
  std::cin >> n >> k;
  GetAns(n, k);
}
