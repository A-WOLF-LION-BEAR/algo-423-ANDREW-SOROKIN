// 131033662
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

void StupidSort(std::vector<std::pair<int, int>>& nums, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      if (nums[i].first > nums[j].first) {
        std::swap(nums[i], nums[j]);
      }
    }
  }
}
int Findlen(int l, int r) {
  int i = 2;
  int kol = 1;
  while (i <= r - l + 1) {
    i *= 2;
    ++kol;
  }
  return kol - 1;
}
std::pair<int, int> GetPair(std::pair<int, int> l, std::pair<int, int> r,
                            std::vector<int>& num) {
  std::pair<int, int> ans;
  int kolind = 2;
  std::vector<std::pair<int, int>> indexes;
  indexes.push_back({num[l.first], l.first});
  indexes.push_back({num[l.second], l.second});
  if (r.first != l.first && r.first != l.second) {
    indexes.push_back({num[r.first], r.first});
    ++kolind;
  }
  if (r.second != l.first && r.second != l.second) {
    indexes.push_back({num[r.second], r.second});
    ++kolind;
  }
  StupidSort(indexes, kolind);
  ans.first = indexes[0].second;
  ans.second = indexes[1].second;
  return ans;
}
void Inputs(int n, std::vector<int>& nums) {
  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }
}
std::vector<std::vector<std::pair<int, int>>> Build(
    int n, std::vector<int>& nums,
    std::vector<std::vector<std::pair<int, int>>>& firandsec) {
  int step = 2;
  int ki = 1;
  for (int i = 0; i < n - 1; ++i) {
    firandsec[ki][i] = {nums[i] < nums[i + 1] ? i : i + 1,
                        nums[i] >= nums[i + 1] ? i : i + 1};
  }
  ++ki;
  step *= 2;
  while (step <= n) {
    for (int i = 0; i < n - step + 1; ++i) {
      firandsec[ki][i] = GetPair(firandsec[ki - 1][i],
                                 firandsec[ki - 1][i + (step / 2)], nums);
    }
    step *= 2;
    ++ki;
  }
  return firandsec;
}
void GetAns(int q, std::vector<std::vector<std::pair<int, int>>>& finders,
            std::vector<int>& num) {
  int l;
  int r;
  for (int i = 0; i < q; ++i) {
    std::cin >> l >> r;
    int len = Findlen(l, r);
    std::cout
        << num[GetPair(finders[len][l - 1], finders[len][r - pow(2, len)], num)
                   .second]
        << "\n";
  }
}
void Print(std::vector<std::vector<std::pair<int, int>>> finders, int n) {
  --n;
  int m = int(log(n));
  for (int i = 0; i < m + 2; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << finders[i][j].first << " " << finders[i][j].second << "   ";
    }
    std::cout << "\n";
  }
}
int main() {
  int n;
  int q;
  std::cin >> n >> q;
  std::vector<int> nums(n);
  Inputs(n, nums);
  std::vector<std::vector<std::pair<int, int>>> finders(
      (int(log2(n)) + 1), std::vector<std::pair<int, int>>(n));
  finders = Build(n, nums, finders);
  // Print(finders, n);
  GetAns(q, finders, nums);
}
