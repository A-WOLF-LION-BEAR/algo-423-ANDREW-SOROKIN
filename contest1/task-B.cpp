// 119761345
#include <algorithm>
#include <iostream>
#include <vector>

const long long cInf = 10004321;
const long long cN45 = 45;
const long long cN123 = 123;

long long FindPivot(std::vector<long long> mas) {
  long long answer;
  if (int(mas.size()) <= 5) {
    std::sort(mas.begin(), mas.end());
    answer = mas[int(mas.size()) / 2];
  } else {
    long long size = int(mas.size()) / 5;
    std::vector<long long> delen(size);
    for (long long i = 0; i < size; i++) {
      std::vector<long long> a = {mas[5 * i], mas[5 * i + 1], mas[5 * i + 2],
                                  mas[5 * i + 3], mas[5 * i + 4]};
      std::sort(a.begin(), a.end());
      delen[i] = a[int(a.size()) / 2];
    }
    if (5 * size < int(mas.size())) {
      std::vector<long long> ostat(mas.end() - (int(mas.size()) - (5 * size)),
                                   mas.end());
      std::sort(ostat.begin(), ostat.end());
      delen.push_back(ostat[int(ostat.size()) / 2]);
    }
    answer = FindPivot(delen);
  }
  return answer;
}

std::vector<long long> CreateMassiv(long long n, long long a0, long long a1) {
  std::vector<long long> chisla(n);
  chisla[0] = a0;
  chisla[1] = a1;
  for (long long i = 2; i < n; i++) {
    if (((chisla[i - 1] * cN123) + (chisla[i - 2] * cN45)) >= cInf) {
      long long per = ((chisla[i - 1] * cN123) + (chisla[i - 2] * cN45));
      while (per >= cInf) {
        per -= cInf;
      }
      chisla[i] = per;
    } else {
      chisla[i] = ((chisla[i - 1] * cN123) + (chisla[i - 2] * cN45));
    }
  }
  return chisla;
}

std::vector<long long> Partition(const std::vector<long long>& massiv,
                                 long long pivot) {
  long long b = 0;
  long long c = 0;
  long long d = 0;
  for (long long i = 0; i < int(massiv.size()); i++) {
    if (massiv[i] < pivot) {
      b++;
    } else if (massiv[i] == pivot) {
      c++;
    } else {
      d++;
    }
  }
  std::vector<long long> bcd = {b, c, d};
  return bcd;
}

std::vector<long long> QSArray(const std::vector<long long>& massiv,
                               long long pivot, int n) {
  std::vector<long long> d;
  if (n == 1) {
    for (long long i = 0; i < int(massiv.size()); i++) {
      if (massiv[i] < pivot) {
        d.push_back(massiv[i]);
      }
    }
  } else {
    for (long long i = 0; i < int(massiv.size()); i++) {
      if (massiv[i] > pivot) {
        d.push_back(massiv[i]);
      }
    }
  }
  return d;
}

long long QuikeSelekt(const std::vector<long long>& massiv, long long neednum) {
  long long answer = 0;
  if (massiv.size() <= 1) {
    answer = massiv[0];
  } else {
    long long pivot = FindPivot(massiv);
    std::vector<long long> index = Partition(massiv, pivot);
    long long l = index[0];
    long long m = index[1];
    if (l <= neednum && neednum < l + m) {
      answer = pivot;
    } else if (neednum < l) {
      answer = QuikeSelekt(QSArray(massiv, pivot, 1), neednum);
    } else if (neednum >= m + l) {
      answer = QuikeSelekt(QSArray(massiv, pivot, 0), neednum - l - m);
    }
  }
  return answer;
}

int main() {
  long long n;
  long long k;
  long long a0;
  long long a1;
  std::cin >> n >> k >> a0 >> a1;
  k--;
  std::vector<long long> numbers = CreateMassiv(n, a0, a1);
  std::cout << QuikeSelekt(numbers, k) << "\n";
}
