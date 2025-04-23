#include <iostream>

class Solution {
 public:
  int binary_search(int arr[], int len) {
    int l = 0, r = len - 1;
    while (l < r) {
      int m = l + (r - l) / 2;
      if (arr[m] < m) {
        l = m + 1;
      } else if (arr[m] > m) {
        r = m - 1;
      } else {
        r = m;
      }
    }
    return (arr[l] == l) ? l : -1;
  }
};

int main() {
  int a[7] = {-1, 1, 2, 3, 5, 8, 9};

  Solution solution = Solution();
  int idx = solution.binary_search(a, 7);
  std::cout << "idx: " << idx << std::endl;
}