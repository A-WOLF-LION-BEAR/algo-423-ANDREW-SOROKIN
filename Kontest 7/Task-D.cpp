// 134915867
#include <algorithm>
#include <iostream>
#include <vector>

struct Global {
  std::vector<std::vector<int>> mat;
  std::vector<std::vector<int>> mat_rev;
  std::vector<int> color;
  std::vector<int> komp;
  std::vector<std::pair<int, int>> top_sort;  // {ind, tout}
  int timer = 0;
  int k = 1;
};

bool SortRule(std::pair<int, int> a, std::pair<int, int> b) {
  return a.second > b.second;
}

void Dfs(int ind, bool is_r, int k, Global& info) {
  info.color[ind] = 1;
  info.komp[ind] = is_r ? k : info.komp[ind];
  ++info.timer;
  for (int bro : (is_r ? info.mat_rev : info.mat)[ind]) {
    if (info.color[bro] == 0) {
      Dfs(bro, is_r, info.k, info);
    }
  }
  std::pair<int, int> a_help = {ind, info.timer};
  info.top_sort[ind] = is_r ? info.top_sort[ind] : a_help;
  ++info.timer;
  info.color[ind] = 2;
}

void Do(int n, Global& info) {
  bool is_r = false;
  for (int ind = 0; ind < n; ++ind) {
    if (info.color[ind] == 0) {
      Dfs(ind, is_r, info.k, info);
    }
  }
  is_r = true;
  std::sort(info.top_sort.begin(), info.top_sort.end(), SortRule);
  info.color = std::vector<int>(n);
  for (auto ind : info.top_sort) {
    if (info.color[ind.first] == 0) {
      Dfs(ind.first, is_r, info.k, info);
      ++info.k;
    }
  }
  std::cout << info.k - 1 << "\n";
}

void Input(int n, int m, Global& info) {
  info.color = std::vector<int>(n);  // white - 0  gray - 1  black - 2
  info.mat = std::vector<std::vector<int>>(n);
  info.mat_rev = std::vector<std::vector<int>>(n);
  info.top_sort = std::vector<std::pair<int, int>>(n);
  info.komp = std::vector<int>(n);
  int u = 0;
  int v = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v;  // u -> v
    info.mat[u - 1].push_back(v - 1);
    info.mat_rev[v - 1].push_back(u - 1);
  }
}

void Output(Global& info) {
  for (auto x : info.komp) {
    std::cout << x << " ";  // k - x << " ";
  }
  std::cout << "\n";
}

int main() {
  int n = 0;
  int m = 0;
  Global info;
  std::cin >> n >> m;
  Input(n, m, info);
  Do(n, info);
  Output(info);
}
