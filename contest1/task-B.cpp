// 125684331
#include <algorithm>
#include <iostream>
#include <vector>

const int64_t cInf = 10004321;
const int64_t cN45 = 45;
const int64_t cN123 = 123;

int64_t FindPivot(std::vector<int64_t> mas) {
  int64_t answer;
  if (int(mas.size()) <= 5) {
    std::sort(mas.begin(), mas.end());
    answer = mas[int(mas.size()) / 2];
  } else {
    int64_t size = int(mas.size()) / 5;
    std::vector<int64_t> delen(size);
    for (int64_t i = 0; i < size; i++) {
      std::vector<int64_t> a = {mas[5 * i], mas[5 * i + 1], mas[5 * i + 2],
                                mas[5 * i + 3], mas[5 * i + 4]};
      std::sort(a.begin(), a.end());
      delen[i] = a[int(a.size()) / 2];
    }
    if (5 * size < int(mas.size())) {
      std::vector<int64_t> ostat(mas.end() - (int(mas.size()) - (5 * size)),
                                 mas.end());
      std::sort(ostat.begin(), ostat.end());
      delen.push_back(ostat[int(ostat.size()) / 2]);
    }
    answer = FindPivot(delen);
  }
  return answer;
}

std::vector<int64_t> Createarray(int64_t n, int64_t a0, int64_t a1) {
  std::vector<int64_t> nums(n);
  nums[0] = a0;
  nums[1] = a1;
  for (int64_t i = 2; i < n; i++) {
    if (((nums[i - 1] * cN123) + (nums[i - 2] * cN45)) >= cInf) {
      int64_t per = ((nums[i - 1] * cN123) + (nums[i - 2] * cN45));
      while (per >= cInf) {
        per -= cInf;
      }
      nums[i] = per;
    } else {
      nums[i] = ((nums[i - 1] * cN123) + (nums[i - 2] * cN45));
    }
  }
  return nums;
}

std::vector<int64_t> Partition(const std::vector<int64_t>& array,
                               int64_t pivot) {
  int64_t b = 0;
  int64_t c = 0;
  int64_t d = 0;
  for (int64_t i = 0; i < int(array.size()); i++) {
    if (array[i] < pivot) {
      b++;
    } else if (array[i] == pivot) {
      c++;
    } else {
      d++;
    }
  }
  std::vector<int64_t> bcd = {b, c, d};
  return bcd;
}

std::vector<int64_t> QSArray(const std::vector<int64_t>& array, int64_t pivot,
                             int n) {
  std::vector<int64_t> d;
  if (n == 1) {
    for (int64_t i = 0; i < int(array.size()); i++) {
      if (array[i] < pivot) {
        d.push_back(array[i]);
      }
    }
  } else {
    for (int64_t i = 0; i < int(array.size()); i++) {
      if (array[i] > pivot) {
        d.push_back(array[i]);
      }
    }
  }
  return d;
}

int64_t QuikeSelekt(const std::vector<int64_t>& array, int64_t neednum) {
  int64_t answer = 0;
  if (array.size() <= 1) {
    answer = array[0];
  } else {
    int64_t pivot = FindPivot(array);
    std::vector<int64_t> index = Partition(array, pivot);
    int64_t l = index[0];
    int64_t m = index[1];
    if (l <= neednum && neednum < l + m) {
      answer = pivot;
    } else if (neednum < l) {
      answer = QuikeSelekt(QSArray(array, pivot, 1), neednum);
    } else if (neednum >= m + l) {
      answer = QuikeSelekt(QSArray(array, pivot, 0), neednum - l - m);
    }
  }
  return answer;
}

int mainTaskB() {
  int64_t n;
  int64_t k;
  int64_t a0;
  int64_t a1;
  std::cin >> n >> k >> a0 >> a1;
  k--;
  std::vector<int64_t> numbers = Createarray(n, a0, a1);
  std::cout << QuikeSelekt(numbers, k) << "\n";
}
