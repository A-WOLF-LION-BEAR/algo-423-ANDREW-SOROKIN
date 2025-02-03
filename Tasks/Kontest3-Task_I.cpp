// 131851538
#include <cstdint>
#include <iostream>
#include <vector>

struct Node {
  std::vector<int> sorted;
  int kol = 0;
  int l = -1;
  int r = -1;
};
int GetLen(int n) {
  int i = 1;
  while (i < n) {
    i *= 2;
  }
  return i;
}
std::vector<int> Merge(int l, std::vector<int>& a, int r, std::vector<int>& b) {
  std::pair<int, int> lens = {l, r};
  std::vector<int> i_have_an_apple_i_have_a_pen_uh_appelpen;
  while (l > 0 || r > 0) {
    if (l == 0) {
      i_have_an_apple_i_have_a_pen_uh_appelpen.push_back(b[lens.second - r]);
      --r;
    } else if (r == 0) {
      i_have_an_apple_i_have_a_pen_uh_appelpen.push_back(a[lens.first - l]);
      --l;
    } else {
      if (b[lens.second - r] > a[lens.first - l]) {
        i_have_an_apple_i_have_a_pen_uh_appelpen.push_back(a[lens.first - l]);
        --l;
      } else {
        i_have_an_apple_i_have_a_pen_uh_appelpen.push_back(b[lens.second - r]);
        --r;
      }
    }
  }
  return i_have_an_apple_i_have_a_pen_uh_appelpen;
}
std::vector<Node> Build(int n, int len) {
  std::vector<Node> tree(len * 2);
  int x;
  for (int i = 0; i < n; ++i) {
    std::cin >> x;
    tree[len + i - 1].sorted.push_back(x);
    ++tree[len + i - 1].kol;
    tree[len + i - 1].l = i;
    tree[len + i - 1].r = i;
  }
  for (int i = len - 2; i >= 0; --i) {
    tree[i].kol = tree[i * 2 + 1].kol + tree[i * 2 + 2].kol;
    tree[i].sorted = Merge(tree[i * 2 + 1].kol, tree[i * 2 + 1].sorted,
                           tree[i * 2 + 2].kol, tree[i * 2 + 2].sorted);
    tree[i].l = tree[i * 2 + 1].l;
    tree[i].r = tree[i * 2 + 2].r < 0 ? tree[i * 2 + 1].r : tree[i * 2 + 2].r;
  }
  return tree;
}
int BinFind(std::vector<int>& array, int x, int len) {
  int l = -1;
  int r = len;
  int mid = (l + r) / 2;
  while (l + 1 < r) {
    if (array[mid] > x) {
      r = mid;
    } else {
      l = mid;
    }
    mid = (l + r) / 2;
  }
  return (mid % 2 == 1 ? l + 1 : (mid == r ? mid : mid + 1));
}
int Find(std::vector<Node>& tree, int r, int x, int len) {
  int i = 0;
  int ans = 0;
  while (len - 1 > i) {
    if (tree[i].r == r) {
      return BinFind(tree[i].sorted, x, tree[i].kol);
    }
    if (tree[i * 2 + 1].r < r) {
      ans += BinFind(tree[i * 2 + 1].sorted, x, tree[i * 2 + 1].kol);
      i = i * 2 + 2;
    } else if (tree[i * 2 + 1].r == r) {
      return ans + BinFind(tree[i * 2 + 1].sorted, x, tree[i * 2 + 1].kol);
    } else {
      i = i * 2 + 1;
    }
  }
  return ans;
}
void GetAns(int q, int len, std::vector<Node>& tree) {
  int x;
  int y;
  int l;
  int r;
  for (int i = 0; i < q; ++i) {
    std::cin >> l >> r >> x >> y;
    int koly = Find(tree, r - 1, y, len) - Find(tree, r - 1, x - 1, len);
    int kolx = Find(tree, l - 2, y, len) - Find(tree, l - 2, x - 1, len);
    std::cout << koly - kolx << "\n";
  }
}
int main() {
  int n;
  int q;
  std::cin >> n >> q;
  int len = GetLen(n);
  std::vector<Node> tree = Build(n, len);
  GetAns(q, len, tree);
}
