// 130505082
#include <algorithm>
#include <iostream>
#include <vector>
std::vector<std::vector<int>> Input(int n) {
  std::vector<std::vector<int>> a(n, std::vector<int>(2));
  for (int i = 0; i < n; i++) {
    std::cin >> a[i][0] >> a[i][1];
  }
  return a;
}
void SamePatrOfCode(int& i, int& j, std::vector<std::vector<int>>& b, int& ib,
                    std::vector<std::vector<int>>& pod1,
                    std::vector<std::vector<int>>& pod2) {
  ++ib;
  if (i < int(pod1.size()) && j < int(pod2.size())) {
    if (pod1[i][0] <= pod2[j][0]) {
      b[ib] = pod1[i];
      i += 1;
    } else {
      b[ib] = pod2[j];
      j += 1;
    }
  } else {
    if (i < int(pod1.size())) {
      b[ib] = pod1[i];
      i += 1;
    } else {
      b[ib] = pod2[j];
      j += 1;
    }
  }
}
void AnotherPatrOfCode(int& i, int& j, std::vector<std::vector<int>>& b,
                       int& ib, std::vector<std::vector<int>>& pod1,
                       std::vector<std::vector<int>>& pod2) {
  while (i < int(pod1.size()) || j < int(pod2.size())) {
    if (i < int(pod1.size()) && b[ib][1] >= pod1[i][0]) {
      b[ib][1] = std::max(b[ib][1], pod1[i][1]);
      i++;
    } else if (j < int(pod2.size()) && b[ib][1] >= pod2[j][0]) {
      b[ib][1] = std::max(b[ib][1], pod2[j][1]);
      j++;
    } else {
      SamePatrOfCode(i, j, b, ib, pod1, pod2);
    }
  }
}
std::vector<std::vector<int>> Marger(std::vector<std::vector<int>> pod1,
                                     std::vector<std::vector<int>> pod2,
                                     int l) {
  std::vector<std::vector<int>> b(l, std::vector<int>(2));
  int i = 0;
  int j = 0;
  int ib = 0;
  if (pod1[i][0] <= pod2[j][0]) {
    b[0] = pod1[i];
    i += 1;
  } else {
    b[0] = pod2[j];
    j += 1;
  }
  AnotherPatrOfCode(i, j, b, ib, pod1, pod2);
  return b;
}
std::vector<std::vector<int>> MargeSort(std::vector<std::vector<int>> a,
                                        int l) {
  std::vector<std::vector<int>> b(l, std::vector<int>(2));
  if (l <= 1) {
    b = a;
  } else {
    std::vector<std::vector<int>> pod1(l / 2, std::vector<int>(2));
    std::vector<std::vector<int>> pod2(l - (l / 2), std::vector<int>(2));
    for (int i = 0; i < l / 2; i++) {
      pod1[i] = {a[i][0], a[i][1]};
    }
    for (int i = 0; i < l - (l / 2); i++) {
      pod2[i] = {a[i + (l / 2)][0], a[i + (l / 2)][1]};
    }
    b = Marger(MargeSort(pod1, pod1.size()), MargeSort(pod2, pod2.size()), l);
  }
  return b;
}
void Output(std::vector<std::vector<int>> b) {
  int len = 0;
  for (int i = 0; i < int(b.size()); i++) {
    if (b[i][0] != 0 && b[i][1] != 0) {
      len++;
    }
  }
  std::cout << len << "\n";
  for (int i = 0; i < int(b.size()); i++) {
    if (b[i][0] != 0 && b[i][1] != 0) {
      std::cout << b[i][0] << " " << b[i][1] << "\n";
    }
  }
}
int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> b = MargeSort(Input(n), n);
  Output(b);
}
