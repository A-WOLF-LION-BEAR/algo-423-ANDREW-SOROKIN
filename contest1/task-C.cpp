// 120480718
#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <vector>

const int cI8 = 8;
const int cI256 = 256;

void LSDsort(std::vector<std::vector<int>> arr, int n) {
  std::vector<std::vector<int>> new_sort_array(n, std::vector<int>(cI8));
  std::vector<int> nomera(cI256);
  for (int l = cI8 - 1; l >= 0; l--) {
    std::vector<int> nomera(cI256);
    for (int i = 0; i < n; i++) {
      nomera[arr[i][l]]++;
    }
    for (int i = 1; i < cI256; i++) {
      nomera[i] += nomera[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
      new_sort_array[nomera[arr[i][l]] - 1] = arr[i];
      nomera[arr[i][l]]--;
    }
    arr = new_sort_array;
  }
  for (int i = 0; i < n; i++) {
    uint64_t ans = 0;
    uint64_t kef = 1;
    for (int j = cI8 - 1; j >= 0; j--) {
      ans += new_sort_array[i][j] * kef;
      kef *= cI256;
    }
    std::cout << ans << " ";
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> massiv_of_numbers(n, std::vector<int>(cI8));
  uint64_t per_for_input_numbers;
  for (int i = 0; i < n; i++) {
    int shetchik = 0;
    std::cin >> per_for_input_numbers;
    while (per_for_input_numbers >= 1) {
      massiv_of_numbers[i][cI8 - 1 - shetchik] = per_for_input_numbers % cI256;
      shetchik++;
      per_for_input_numbers /= cI256;
    }
  }
  LSDsort(massiv_of_numbers, n);
}