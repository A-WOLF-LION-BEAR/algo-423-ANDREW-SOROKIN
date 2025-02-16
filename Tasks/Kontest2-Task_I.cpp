// 133451235
#include <iostream>
#include <vector>

struct Node {
  int x;
  int indlbro = 0;
  int indrbro = 0;
};

int StupidMinus(std::vector<Node>& arr, int n, int& koli) {
  int ans = arr[arr[n + 1].indlbro].x;
  arr[arr[arr[n + 1].indlbro].indlbro].indrbro = n + 1;
  arr[n + 1].indlbro = arr[arr[n + 1].indlbro].indlbro;
  --koli;
  return ans;
}

void StupidPlus(std::vector<Node>& arr, int x, int& size, int& koli) {
  arr[size + 1].x = x;
  arr[arr[0].indrbro].indlbro = size + 1;
  arr[size + 1].indrbro = arr[0].indrbro;
  arr[0].indrbro = size + 1;
  arr[size + 1].indlbro = 0;
  ++size;
  ++koli;
}

int Minus(std::vector<Node>& arr, int& koli) {
  int ans;
  ans = arr[arr[0].indrbro].x;
  arr[arr[arr[0].indrbro].indrbro].indlbro = 0;
  arr[0].indrbro = arr[arr[0].indrbro].indrbro;
  --koli;
  return ans;
}

void Plus(std::vector<Node>& arr, int x, int& size, int n, int& koli) {
  arr[size + 1].x = x;
  arr[size + 1].indrbro = n + 1;
  arr[size + 1].indlbro = arr[n + 1].indlbro;
  arr[arr[n + 1].indlbro].indrbro = size + 1;
  arr[n + 1].indlbro = size + 1;
  ++size;
  ++koli;
}

void ReHang(std::vector<Node>& arr1, int& kol1, std::vector<Node>& arr2,
            std::vector<int>& size, int n, int& kol2) {
  while (kol2 > kol1 && kol1 != kol2 && kol1 != kol2 + 1) {
    Plus(arr1, Minus(arr2, kol2), size[0], n, kol1);
  }
  if (kol1 > kol2 + 1) {
    while (kol1 != kol2 && kol1 != kol2 + 1) {
      StupidPlus(arr2, StupidMinus(arr1, n, kol1), size[1], kol2);
    }
  }
}

void Body(int n) {
  std::vector<Node> arr1(n + 2);
  std::vector<Node> arr2(n + 2);
  std::vector<int> size(2);
  int kol1 = 0;
  int kol2 = 0;
  int x;
  char c;
  arr1[0].indrbro = n + 1;
  arr1[n + 1].indlbro = 0;
  arr2[0].indrbro = n + 1;
  arr2[n + 1].indrbro = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> c;
    if (c == '+') {
      std::cin >> x;
      Plus(arr2, x, size[1], n, kol2);
      ReHang(arr1, kol1, arr2, size, n, kol2);
    } else if (c == '*') {
      std::cin >> x;
      Plus(arr1, x, size[0], n, kol1);
      ReHang(arr1, kol1, arr2, size, n, kol2);
    } else if (c == '-') {
      std::cout << Minus(arr1, kol1) << "\n";
      ReHang(arr1, kol1, arr2, size, n, kol2);
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  Body(n);
}
