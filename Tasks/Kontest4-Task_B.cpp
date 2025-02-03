// 131665226
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

const uint64_t cPiDiddy = 1000000000;
struct BBC {
  int ind = -1;
  uint64_t x = 0;
  int lson = -1;
  int rson = -1;
  int father = -1;
  int weight = 0;
};
int Perdel(std::vector<BBC>& arr, BBC& f, BBC& l, BBC& r, int& tail) {
  int ans;
  if (l.weight + 1 > r.weight) {
    if (f.father >= 0 && f.x > arr[f.father].x) {
      arr[f.father].rson = l.ind;
    } else if (f.father >= 0 && f.x < arr[f.father].x) {
      arr[f.father].lson = l.ind;
    } else {
      tail = l.ind;
    }
    l.weight = f.weight;
    f.weight = 1;
    f.lson = l.rson;
    l.rson = f.ind;
    l.father = f.father;
    f.father = l.ind;
    if (f.lson >= 0) {
      arr[f.lson].father = f.ind;
      f.weight += arr[f.lson].weight;
    }
    f.weight += f.rson >= 0 ? arr[f.rson].weight : 0;
    if (l.ind >= 0) {
      arr[l.ind] = l;
    }
    ans = l.father;
  } else {
    if (f.father >= 0 && f.x > arr[f.father].x) {
      arr[f.father].rson = r.ind;
    } else if (f.father >= 0 && f.x < arr[f.father].x) {
      arr[f.father].lson = r.ind;
    } else {
      tail = r.ind;
    }
    r.weight = f.weight;
    f.weight = 1;
    f.rson = r.lson;
    r.lson = f.ind;
    r.father = f.father;
    f.father = r.ind;
    if (f.rson >= 0) {
      arr[f.rson].father = f.ind;
      f.weight += arr[f.rson].weight;
    }
    f.weight += f.lson >= 0 ? arr[f.lson].weight : 0;
    if (r.ind >= 0) {
      arr[r.ind] = r;
    }
    ans = r.father;
  }
  arr[f.ind] = f;
  return ans;
}
void Put(std::vector<BBC>& arr, BBC oort, int& tail) {
  BBC vod;
  int i = tail;
  if (arr[i].x == 0) {
    arr[i] = oort;
    arr[i].father = -3;
    arr[i].weight = 1;
  } else {
    while (i != oort.ind) {
      ++arr[i].weight;
      if (arr[i].x > oort.x) {
        if (arr[i].lson < 0) {
          arr[i].lson = oort.ind;
          oort.father = i;
          arr[oort.ind] = oort;
          i = oort.ind;
        } else {
          i = arr[i].lson;
        }
      } else {
        if (arr[i].rson < 0) {
          oort.father = i;
          arr[i].rson = oort.ind;
          arr[oort.ind] = oort;
          i = oort.ind;
        } else {
          i = arr[i].rson;
        }
      }
    }
    while (i >= 0) {
      BBC l = arr[i].lson != -1 ? arr[arr[i].lson] : vod;
      BBC r = arr[i].rson != -1 ? arr[arr[i].rson] : vod;
      l.father = i;
      r.father = i;
      if (abs(l.weight - r.weight) > 1) {
        i = Perdel(arr, arr[i], l, r, tail);
      } else {
        i = arr[i].father;
      }
    }
  }
}

bool IsIn(std::vector<BBC>& tf, uint64_t x, int& tail) {
  int i = tail;
  while (i != -1) {
    if (tf[i].x == x) {
      return true;
    }
    i = tf[i].x > x ? tf[i].lson : tf[i].rson;
  }
  return false;
}
int Find(std::vector<BBC>& tf, uint64_t x, int& tail) {
  int i = tail;
  uint64_t min = 0;
  while (i != -1) {
    if (tf[i].x == x) {
      return x;
    }
    if (tf[i].x > x) {
      min = min > 0 ? std::min(min, tf[i].x) : tf[i].x;
    }
    i = tf[i].x > x ? tf[i].lson : tf[i].rson;
  }
  return min < x ? -1 : min;
}
void Get(std::vector<BBC>& tf, int n, int& tail) {
  uint64_t x;
  char c;
  int kol = 0;
  BBC a;
  std::pair<int, bool> last;
  for (int i = 0; i < n; ++i) {
    std::cin >> c >> x;
    if (c == '+') {
      if (last.second) {
        x = (x + last.first) % cPiDiddy;
      }
      if (!IsIn(tf, x, tail)) {
        a.x = x;
        a.weight = 1;
        a.ind = kol;
        Put(tf, a, tail);
        ++kol;
      }
      last.second = false;
    } else if (c == '?') {
      int ans = Find(tf, x, tail);
      last.first = ans;
      last.second = true;
      std::cout << ans << "\n";
    }
  }
}
int main() {
  int n;
  int tail = 0;
  std::cin >> n;
  std::vector<BBC> tf2(n + 1);
  Get(tf2, n, tail);
}
