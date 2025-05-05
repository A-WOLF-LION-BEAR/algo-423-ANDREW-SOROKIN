// 133138322
#include <iostream>
#include <vector>

const int cInf = 2147483647;

struct Node {
  int x = cInf;
  int len = 0;
  std::vector<int> points;
};

int BinFind(std::vector<Node>& dp, int x) {
  int l = 0;
  int r = int(dp.size());
  int mid = (l + r) / 2;
  while (l + 1 < r) {
    (dp[mid].x >= x ? r : l) = mid;
    mid = (l + r) / 2;
  }
  while (dp[mid].x >= x) {
    --mid;
  }
  ++mid;
  return mid;
}
void Input(std::vector<Node>& dp, std::vector<int>& nums, int n) {
  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }
  dp[0].x = -cInf;
}
void BuildDP(std::vector<Node>& dp, std::vector<int>& nums, int n) {
  int k = 0;
  for (int i = 0; i < n; ++i) {
    k = BinFind(dp, nums[i]);
    dp[k].len += 1;
    dp[k].x = nums[i];
    dp[k].points.push_back(i + 1);
  }
}
void GetAns(std::vector<Node>& dp, int n) {
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    ans = (dp[ans].len > dp[i].len ? ans : i);
  }
  std::cout << dp[ans].len << "\n";
  for (int i : dp[ans].points) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<int> nums(n);
  std::vector<Node> dp(n);
  Input(dp, nums, n);
  BuildDP(dp, nums, n);
  GetAns(dp, n);
}
