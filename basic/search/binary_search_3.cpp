#include <iostream>

class Solution {
 public:
  int binary_search(int arr[], int len, int key) {
    int l = 0, r = len - 1;
    while (l <= r) {
      int m = l + (r - l) / 2;
      if (arr[m] < key) {
        l = m + 1;
      } else {
        if (m == 0 || arr[m - 1] < key) {
          return m;
        }
        r = m - 1;
      }
    }
    return -1;
  }
};

int main() {
  int a[6] = {1, 2, 3, 5, 5, 7};

  Solution solution = Solution();
  int idx = solution.binary_search(a, 6, 6);
  std::cout << "idx: " << idx << std::endl;
}