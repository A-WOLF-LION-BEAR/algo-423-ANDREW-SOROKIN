// 135133456
// 1
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Global {
  std::vector<std::vector<std::pair<int, int>>> mat;  // {ind, num}
  std::vector<int> fup;
  std::vector<int> tin;
  std::vector<bool> used;
  std::map<std::pair<int, int>, std::vector<int>> bro_mat;  // {head, rail, num}
  std::vector<int> bridges;
  std::map<int, int> bad_gays;
  int timer = 0;
  Global(int n)
      : mat(std::vector<std::vector<std::pair<int, int>>>(n)),
        fup(std::vector<int>(n)),
        tin(std::vector<int>(n)),
        used(std::vector<bool>(n, false)) {}
};

void Dfs(int ind, int num, int parent, Global& info) {
  info.tin[ind] = info.timer++;
  info.used[ind] = true;
  info.fup[ind] = info.tin[ind];
  for (auto to : info.mat[ind]) {
    if (to.first == parent) {
      continue;
    }
    if (info.used[to.first]) {
      info.fup[ind] = std::min(info.fup[ind], info.tin[to.first]);
    } else {
      Dfs(to.first, to.second, ind, info);
      info.fup[ind] = std::min(info.fup[ind], info.fup[to.first]);
    }
  }
  if (info.fup[ind] >= info.tin[ind] && parent != -1) {
    info.bridges.push_back(num);
  }
}

void Do(int n, Global& info) {
  for (int ind = 0; ind < n; ++ind) {
    if (!info.used[ind]) {
      Dfs(ind, -1, -1, info);
    }
  }
  std::vector<int> ans;
  std::sort(info.bridges.begin(), info.bridges.end());
  for (auto br : info.bridges) {
    if (!info.bad_gays.contains(br)) {
      ans.push_back(br);
    }
  }
  std::cout << ans.size() << "\n";
  for (auto br : ans) {
    std::cout << br << " ";
  }
  std::cout << (!ans.empty() ? "\n" : "");
}

void Input(int m, Global& info) {
  int u = 0;
  int v = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v;  // u <-> v
    std::pair<int, int> bloc = {(u > v ? v : u), (u > v ? u : v)};
    if (info.bro_mat.contains(bloc)) {
      if (!info.bad_gays.contains(info.bro_mat[bloc][2])) {
        info.bad_gays[info.bro_mat[bloc][2]] = info.bro_mat[bloc][2];
      }
      info.bad_gays[i + 1] = i + 1;
    } else {
      info.bro_mat[bloc] = {(u > v ? v : u), (u > v ? u : v), i + 1};
    }
    info.mat[u - 1].push_back({v - 1, i + 1});
    info.mat[v - 1].push_back({u - 1, i + 1});
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Global info(n);
  Input(m, info);
  Do(n, info);
}
