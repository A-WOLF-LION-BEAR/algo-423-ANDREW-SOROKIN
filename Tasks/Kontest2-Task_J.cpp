// 131803960
#include <iostream>
#include <string>
#include <vector>

struct Node {
  int x = -1;
  int lbro = 0;
  int rbro = 0;
  int min = -1;
};
void Plus(std::vector<Node>& och, int x, int& size, int n, int& kol) {
  och[size + 1].x = x;
  och[size + 1].rbro = n + 1;
  och[size + 1].lbro = och[n + 1].lbro;
  och[och[n + 1].lbro].rbro = size + 1;
  och[n + 1].lbro = size + 1;
  och[size + 1].min = std::min(
      x,
      (och[och[size + 1].lbro].min > 0 ? och[och[size + 1].lbro].min : x + 1));
  ++size;
  ++kol;
}
int Delet(std::vector<Node>& och, int n, int& kol) {
  --kol;
  int ans = och[och[n + 1].lbro].x;
  och[och[och[n + 1].lbro].lbro].rbro = n + 1;
  och[n + 1].lbro = och[och[n + 1].lbro].lbro;
  return ans;
}
void Skid(std::vector<Node>& nach, std::vector<Node>& kon,
          std::vector<int>& size, std::vector<int>& kol, int n) {
  while (kol[0] > 0) {
    Plus(kon, Delet(nach, n, kol[0]), size[1], n, kol[1]);
  }
}
void Body(int n) {
  std::vector<int> size(2);
  std::vector<int> kol(2);
  std::string s;
  int x;
  std::vector<Node> nach(n + 2);
  std::vector<Node> kon(n + 2);
  nach[0].rbro = n + 1;
  nach[n + 1].lbro = 0;
  kon[0].rbro = n + 1;
  kon[n + 1].lbro = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> s;
    if (s == "size") {
      std::cout << kol[0] + kol[1] << "\n";
    } else if (s == "enqueue") {
      std::cin >> x;
      Plus(nach, x, size[0], n, kol[0]);
      std::cout << "ok\n";
    } else if (s == "dequeue") {
      if (kol[0] + kol[1] > 0) {
        if (kol[1] == 0) {
          Skid(nach, kon, size, kol, n);
        }
        std::cout << Delet(kon, n, kol[1]) << "\n";
      } else {
        std::cout << "error\n";
      }
    } else if (s == "front") {
      if (kol[0] + kol[1] > 0) {
        if (kol[1] == 0) {
          Skid(nach, kon, size, kol, n);
        }
        std::cout << kon[kon[n + 1].lbro].x << "\n";
      } else {
        std::cout << "error\n";
      }
    } else if (s == "clear") {
      kol[0] = 0;
      kol[1] = 0;
      nach[0].rbro = n + 1;
      nach[n + 1].lbro = 0;
      kon[0].rbro = n + 1;
      kon[n + 1].lbro = 0;
      std::cout << "ok\n";
    } else if (s == "min") {
      if (kol[0] + kol[1] > 0) {
        int m1 = kol[0] > 0 ? nach[nach[n + 1].lbro].min : -1;
        int m2 = kol[1] > 0 ? kon[kon[n + 1].lbro].min : -1;
        std::cout << std::min((m1 == -1 ? m2 + 1 : m1),
                              (m2 == -1 ? m1 + 1 : m2))
                  << "\n";
      } else {
        std::cout << "error\n";
      }
    }
  }
}
int main() {
  int n;
  std::cin >> n;
  Body(n);
}
